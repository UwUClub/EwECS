#include "EwECS/Network/NetworkHandler.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include "EwECS/Network/Serialization.hpp"

namespace ECS::Network {

    using boost::asio::ip::udp;

    void NetworkHandler::start(const boost::asio::basic_socket<boost::asio::ip::udp>::protocol_type &aProtocol,
                               PacketFactory &aPacketFactory)
    {
        _packetFactory = aPacketFactory;
        _socket.open(aProtocol);
        listen();
    }

    void NetworkHandler::bind(const udp::endpoint &aEndpoint)
    {
        _socket.bind(aEndpoint);
    }

    void NetworkHandler::onReceive(ReceiveCallback aOnReceive)
    {
        _onReceive = aOnReceive;
    }

    void NetworkHandler::listen()
    {
        try {
            _readBuffer = _readInbound.prepare(READ_BUFFER_SIZE);
            _socket.async_receive_from(boost::asio::buffer(_readBuffer), _readEndpoint,
                                    boost::bind(&NetworkHandler::tryHandleRequest, this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));

            if (!_ioThread.joinable()) {
                _ioThread = boost::thread(boost::bind(&boost::asio::io_service::run, &_ioService));
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void NetworkHandler::tryHandleRequest(const boost::system::error_code &aError, std::size_t aBytesTransferred)
    {
        (void) aError;

        try {
            _readInbound.commit(aBytesTransferred);
            auto buff = Buffer(boost::asio::buffers_begin(_readInbound.data()),
                               boost::asio::buffers_begin(_readInbound.data()) + aBytesTransferred);
            auto header = unserialize<PacketHeader>(buff);
            int type = header.type;
            std::string uuid(header.uuid);

            IPayload *payload = nullptr;

            if (type < ERROR_PACKET_TYPE) {
                throw std::runtime_error("Invalid packet type");
            }
            if (_packetFactory.find(type) != _packetFactory.end()) {
                buff.erase(buff.begin(), buff.begin() + sizeof(PacketHeader));
                payload = _packetFactory[type](buff);
                if (payload == nullptr) {
                    throw std::runtime_error("Invalid payload");
                }
            }

            if (header.type == AKNOWLEDGMENT_PACKET_TYPE) { // receive aknowledgment
                if (_senders.find(uuid) != _senders.end() && _senders[uuid].first.joinable()) {
                    _senders[uuid].second = false;
                    _senders[uuid].first.join();
                    _senders.erase(uuid);
                }
            } else if (header.type >= 0) { // send aknowledgment
                sendAknowledgment(uuid, _readEndpoint);
            }
            _onReceive(header.type, payload, _readEndpoint);
        } catch (const std::exception &e) {
            send(ERROR_PACKET_TYPE, _readEndpoint);
        }
        try {
            _readInbound.consume(_readInbound.size());
            listen();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void NetworkHandler::send(int8_t aType, const udp::endpoint &aEndpoint)
    {
        try {
            PacketHeader header(aType);

            std::vector<uint8_t> strBuff = serialize(header);
            _socket.send_to(boost::asio::buffer(strBuff), aEndpoint);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void NetworkHandler::sendAknowledgment(std::string &aUuid, const udp::endpoint &aEndpoint)
    {
        try {
            PacketHeader header(AKNOWLEDGMENT_PACKET_TYPE, aUuid);

            std::vector<uint8_t> strBuff = serialize(header);
            _socket.send_to(boost::asio::buffer(strBuff), aEndpoint);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

    boost::asio::io_service &NetworkHandler::getIoService()
    {
        return _ioService;
    }

    void NetworkHandler::stop()
    {
        try {
            for (auto &sender : _senders) {
                sender.second.second = false;
                if (sender.second.first.joinable()) {
                    sender.second.first.join();
                }
            }
            _ioService.stop();
            if (_ioThread.joinable()) {
                _ioThread.join();
            }
            _socket.close();
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }

} // namespace ECS::Network
