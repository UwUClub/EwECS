#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "Connection.hpp"
#include "EwECS/SparseArray.hpp"
#include "NetworkHandler.hpp"
#include "Packet.hpp"
#include <unordered_map>

#ifndef SERVERHANDLER_HPP
    #define SERVERHANDLER_HPP

namespace ECS::Network {

    constexpr unsigned short READ_BUFFER_SIZE = 1024;

    using boost::asio::ip::udp;
    using ServerReceiveCallback = std::function<void(int8_t, IPayload *, unsigned short)>;
    using ServerReceiveAknowledgmentCallback = std::function<void(unsigned short)>;

    class ServerHandler
    {
        private:
            std::unordered_map<size_t, udp::endpoint> _clients;
            std::vector<std::unique_ptr<udp::endpoint>> _waitingQueue = std::vector<std::unique_ptr<udp::endpoint>>();
            ServerReceiveCallback _onReceive;
            ServerReceiveAknowledgmentCallback _onReceiveAknowledgment;
            unsigned short _maxClients = 0;

            /**
             * @brief Launch the server
             */
            ServerHandler() = default;

            /**
             * @brief Handle a packet reception
             * @param aType The packet type
             * @param aPayload The packet payload
             * @param aClientEndpoint The endpoint of the sender
             */
            void handlePacket(uint8_t aType, IPayload *aPayload, const udp::endpoint &aClientEndpoint);

            /**
             * @brief Handle aknowledgment reception
             * @param aEndpoint The endpoint of the sender
             */
            void handleAknowledgment(const udp::endpoint &);

        public:
            /**
             * @brief Destroy the ServerHandler object
             */
            ~ServerHandler() = default;

            /**
             * @brief Get the instance of the singleton
             * @return ServerHandler & The instance of the singleton
             */
            static ServerHandler &getInstance()
            {
                static ServerHandler instance;
                return instance;
            }

            /**
             * @brief Start the server
             * @param aHost The host to listen to
             * @param aPort The port to listen to
             * @param aMaxClients The maximum number of clients
             * @param aPacketFactory The packet factory
             * @return ServerHandler & The instance of the singleton
             */
            void start(std::string &, unsigned short, unsigned short, PacketFactory &);

            /**
             * @brief Set the on receive callback
             * @param aOnReceive The callback to set
             */
            void onReceive(ServerReceiveCallback);

            /**
             * @brief Set the on receive aknowledgment callback
             * @param aOnReceiveAknowledgment The callback to set
             */
            void onReceiveAknowledgment(ServerReceiveAknowledgmentCallback);

            /**
             * @brief Register a client to the server
             * @param aClientId The id of the client
             */
            void addClient(unsigned short);

            /**
             * @brief Remove a client from the server
             * @param aClientId The id of the client to remove
             */
            void removeClient(size_t);

            /**
             * @brief Get the number of clients connected to the server
             * @return int The number of clients connected to the server
             */
            int getNumberClients() const;

            /**
             * @brief Tell the client there is an error
             * @param aClientId The id of the client to send the message to
             */
            void sendError(unsigned short aClientId);

            /**
             * @brief Send a packet to a client
             * @param aHeader The packet header
             * @param aPayload The packet payload
             * @param aClientId The id of the client to send the message to
             */
            template<typename Payload>
            void send(PacketHeader &aHeader, Payload &aPayload, unsigned short aClientId,
                      ECS::Core::SparseArray<Component::Connection> &aConnection)
            {
                if (aConnection[aClientId].has_value()) {
                    aConnection[aClientId].value().status = ConnectionStatus::PENDING;
                    NetworkHandler::getInstance().send<Payload>(aHeader, aPayload, _clients[aClientId]);
                }
            }

            /**
             * @brief Send a packet to a client
             * @param aType The packet type to send
             * @param aPayload The packet payload
             * @param aClientId The id of the client to send the message to
             */
            template<typename Payload>
            void send(int8_t aType, Payload &aPayload, unsigned short aClientId,
                      ECS::Core::SparseArray<Component::Connection> &aConnection)
            {
                if (aConnection[aClientId].has_value()) {
                    aConnection[aClientId].value().status = ConnectionStatus::PENDING;
                    NetworkHandler::getInstance().send<Payload>(aType, aPayload, _clients[aClientId]);
                }
            }

            /**
             * @brief Broadcast a message to all clients. Each client receives a packet with a unique uuid.
             * @param aType The packet type to send
             * @param aPayload The payload to send
             * @param aConnections Connection components of clients
             */
            template<typename Payload>
            void broadcast(int8_t aType, Payload &aPayload, ECS::Core::SparseArray<Component::Connection> &aConnection)
            {
                for (auto &client : _clients) {
                    send(aType, aPayload, client.first, aConnection);
                }
            }

            /**
             * @brief Check if the server is full
             * @return true if the server is full, false otherwise
             */
            [[nodiscard]] bool isFull() const;

            /**
             * @brief Stop the server
             */
            void stop();
    };

} // namespace ECS::Network

#endif
