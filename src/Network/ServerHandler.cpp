#include "EwECS/Network/ServerHandler.hpp"
#include <boost/bind.hpp>
#include <iostream>
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Network/NetworkHandler.hpp"
#include "EwECS/Network/Packet.hpp"
#include "EwECS/Network/Values.hpp"
#include "EwECS/World.hpp"
#include "EwECS/Logger.hpp"

namespace ECS::Network {

    using boost::asio::ip::udp;

    void ServerHandler::start(std::string &aHost, unsigned short aPort, unsigned short aMaxClients,
                              PacketFactory &aPacketFactory)
    {
        try {
            auto &world = ECS::Core::World::getInstance();
            world.registerComponent<Component::Connection>();
        } catch (std::exception &e) {
            Logger::error(e.what());
        }

        NetworkHandler &network = NetworkHandler::getInstance();
        udp::endpoint endpoint(boost::asio::ip::address::from_string(aHost), aPort);

        network.onReceive([this](int8_t aType, IPayload *aPayload, udp::endpoint &aClientEndpoint) {
            handlePacket(aType, aPayload, aClientEndpoint);
        });

        _maxClients = aMaxClients;

        _clientIds = std::vector<size_t>(aMaxClients);
        for (int i = 0; i < aMaxClients; i++) {
            _clientIds[i] = -1;
        }

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

    void ServerHandler::onReceive(ServerReceiveCallback aCallback)
    {
        _onReceive = aCallback;
    }

    int ServerHandler::addClient(size_t aClientId)
    {
        if (_waitingQueue.size() > 0) {
            _clients[aClientId] = *_waitingQueue[0];
            _waitingQueue.erase(_waitingQueue.begin());

            for (int i = 0; i < _maxClients; i++) {
                if (_clientIds[i] == -1) {
                    _clientIds[i] = aClientId;
                    std::cout << "Player " << aClientId << " joined" << std::endl;
                    return i;
                }
            }
        }
        return -1;
    }

    int ServerHandler::getClientSeat(size_t aClientId)
    {
        for (int i = 0; i < _maxClients; i++) {
            if (_clientIds[i] == aClientId) {
                return i;
            }
        }
        return -1;
    }

    void ServerHandler::removeClient(size_t aClientId)
    {
        _clients.erase(aClientId);
        for (int i = 0; i < _maxClients; i++) {
            if (_clientIds[i] == aClientId) {
                _clientIds[i] = -1;
            }
        }
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
