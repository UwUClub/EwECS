#include "EwECS/Network/ServerHandler.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Network/NetworkHandler.hpp"
#include "EwECS/Network/Packet.hpp"
#include "EwECS/Network/Values.hpp"

namespace ECS::Network {

    using boost::asio::ip::udp;

    void ServerHandler::start(std::string &aHost, unsigned short aPort, unsigned short aMaxClients,
                              PacketFactory &aPacketFactory)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        udp::endpoint endpoint(boost::asio::ip::address::from_string(aHost), aPort);

        network.onReceive([this](int8_t aType, IPayload *aPayload, udp::endpoint &aClientEndpoint) {
            if (aType == AKNOWLEDGMENT_PACKET_TYPE) {
                handleAknowledgment(aClientEndpoint);
            } else if (aType == ERROR_PACKET_TYPE) {
                // receive error packet
            } else if (aType >= 0) {
                handlePacket(aType, aPayload, aClientEndpoint);
            } else {
                NetworkHandler &network = NetworkHandler::getInstance();
                network.send(ERROR_PACKET_TYPE, aClientEndpoint);
            }
        });

        _maxClients = aMaxClients;

        network.start(endpoint.protocol(), aPacketFactory);
        network.bind(endpoint);
        std::cout << "Server " << endpoint << " listening" << std::endl;
    }

    void ServerHandler::handlePacket(uint8_t aType, IPayload *aPayload, const udp::endpoint &aClientEndpoint)
    {
        auto client = std::find_if(_clients.begin(), _clients.end(),
                                   [aClientEndpoint](const std::pair<size_t, udp::endpoint> &aPair) {
                                       return aPair.second == aClientEndpoint;
                                   });

        unsigned short entityId = 0;
        if (client != _clients.end()) {
            entityId = client->first;
        } else if (aType == CONNECT_PACKET_TYPE) {
            _waitingQueue.push_back(std::make_unique<udp::endpoint>(aClientEndpoint));
        } else {
            return;
        }
        _onReceive(aType, aPayload, entityId);
    }

    void ServerHandler::handleAknowledgment(const udp::endpoint &aClientEndpoint)
    {
        auto client = std::find_if(_clients.begin(), _clients.end(),
                                   [aClientEndpoint](const std::pair<size_t, udp::endpoint> &aPair) {
                                       return aPair.second == aClientEndpoint;
                                   });
        if (client == _clients.end()) {
            return;
        }
        _onReceiveAknowledgment(client->first);
    }

    void ServerHandler::onReceive(ServerReceiveCallback aCallback)
    {
        _onReceive = aCallback;
    }

    void ServerHandler::onReceiveAknowledgment(ServerReceiveAknowledgmentCallback aCallback)
    {
        _onReceiveAknowledgment = aCallback;
    }

    void ServerHandler::addClient(unsigned short aClientId)
    {
        if (_waitingQueue.size() > 0) {
            _clients[aClientId] = *_waitingQueue[0];
            _waitingQueue.erase(_waitingQueue.begin());
            std::cout << "Player " << aClientId << " joined" << std::endl;
        }
    }

    void ServerHandler::removeClient(size_t aClientId)
    {
        _clients.erase(aClientId);
    }

    int ServerHandler::getNumberClients() const
    {
        return _clients.size();
    }

    void ServerHandler::sendError(unsigned short aClientId)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        network.send(ERROR_PACKET_TYPE, _clients[aClientId]);
    }

    bool ServerHandler::isFull() const
    {
        return _clients.size() >= _maxClients;
    }

    void ServerHandler::stop()
    {
        NetworkHandler::getInstance().stop();
    }

} // namespace ECS::Network
