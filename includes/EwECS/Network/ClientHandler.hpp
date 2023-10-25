/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** ClientHandler
*/

#ifndef CLIENTHANDLER_HPP
#define CLIENTHANDLER_HPP

#include <boost/asio.hpp>
#include "EwECS/Utils.hpp"
#include "NetworkHandler.hpp"
#include "Packet.hpp"
#include <unordered_map>

namespace ECS::Network {

    using boost::asio::ip::udp;
    using ClientReceiveCallback = std::function<void(int8_t, IPayload *)>;

    class ClientHandler
    {
        private:
            udp::resolver _resolver;
            udp::endpoint _serverEndpoint;
            ClientReceiveCallback _onReceive;

            /**
             * @brief Get the instance of the singleton
             */
            ClientHandler();

        public:
            /**
             * @brief Destroy the ClientHandler object
             */
            ~ClientHandler() = default;

            /**
             * @brief Get the instance of the singleton
             * @return ClientHandler & The instance of the singleton
             */
            static ClientHandler &getInstance()
            {
                static ClientHandler instance;
                return instance;
            }

            /**
             * @brief Run the client
             * @param aHost The host to connect to
             * @param aPort THe port to connect to
             * @param aPacketFactory The packet factory
             */
            void start(std::string &, std::string &, PacketFactory &);

            /**
             * @brief Set the on receive callback
             * @param aOnReceive The callback to set
             */
            void onReceive(ClientReceiveCallback aOnReceive);

            /**
             * @brief Send a packet to the server
             * @param aType The packet type
             */
            void send(int8_t aType);

            /**
             * @brief Send a packet to the server
             * @param aType The packet type
             * @param aPayload The packet payload
             */
            template<typename Payload>
            void send(int8_t aType, Payload &aPayload)
            {
                NetworkHandler::getInstance().send<Payload>(aType, aPayload, _serverEndpoint);
            }
    };

} // namespace ECS::Network

#endif
