#include "EwECS/Network/ClientHandler.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Network/NetworkHandler.hpp"
#include "EwECS/Network/Packet.hpp"

namespace ECS::Network {

    using boost::asio::ip::udp;

    ClientHandler::ClientHandler()
        : _resolver(udp::resolver(NetworkHandler::getInstance().getIoService()))
    {}

    void ClientHandler::onReceive(ClientReceiveCallback &aOnReceive)
    {
        _onReceive = aOnReceive;
    }

    void ClientHandler::start(std::string &aHost, std::string &aPort, PacketFactory &aPacketFactory)
    {
        NetworkHandler &network = NetworkHandler::getInstance();
        _serverEndpoint = *_resolver.resolve(udp::v4(), aHost, aPort).begin();

        network.onReceive([this](int8_t aType, IPayload *aPayload, udp::endpoint &aEndpoint) {
            (void) aEndpoint;
            if (aEndpoint == _serverEndpoint) {
                if (aType >= 0) {
                    _onReceive(aType, aPayload);
                }
            }
        });

        network.start(udp::v4(), aPacketFactory);
        std::cout << "Connected to " << _serverEndpoint << std::endl;
    }

    void ClientHandler::send(int8_t aType)
    {
        NetworkHandler::getInstance().send(aType, _serverEndpoint);
    }

} // namespace ECS::Network
