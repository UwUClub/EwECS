# Network documentation

## Introduction

The Network part of the ECS handles client / server communication using UDP binary packets with [Boost Asio](https://www.boost.org/doc/libs/1_76_0/doc/html/boost_asio.html).

## Components
 <table>
   <tr>
    <th>Name</th>
    <th>Property name</th>
     <th>Property description</th>
    <th>Property type</th>
   </tr>
   <tr>
    <td><code>Connection</code></td>
    <td>
       <table>
          <tr><td><code>status</code></td></tr>
          <tr><td><code>age</code></td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>Connection status</td></tr>
          <tr><td>Time since the last sign of life sent by client</td></tr>
       </table>
    </td>
    <td>
       <table>
          <tr><td>enum <code>PENDING</code> or <code>CONNECTED</code></td></tr>
          <tr><td>float</td></tr>
       </table>
    </td>
   </tr>
</table>

## Packet

### Format

A packet is a sequence of bytes sent over the UDP connection. It has the following properties:

| Name | Kind | Description |
| - | - | - |
| `uuid` | 36-byte string | Unique id to identify the packet |
| `type` | byte | Packet type |
| `payload` | depends on packet type | Data carried by the packet |

If the packet format is not respected, the server sends back a packet of Error type (see [packet types](#32-packet-types))

### Common types

#### Answer aknowledgment 
|  Type | Bound to | Payload type | Payload size (bytes) |
| - | - | - | - |
| `-1` | Client & Server | empty | empty |

#### Answer error
|  Type | Bound to | Payload type | Payload size (bytes) |
| - | - | - | - |
| `-2` | Client & Server | empty | empty |

You must define your own packet types. They must be >= 0. The client packet of type 0 must be used for connection to the server. It has to be the first packet sent by the client. Otherwise the server will ignore it.

## Handlers

The Network is composed of 3 singleton handlers: ``NetworkHandler``, ``ClientHandler`` and ``ServerHandler``.
``NetworkHandler`` defines common basis features used by client and server, such as packet send / reception.

When using our Network tool you must define a struct for each packet payload. Those struct inherit from ``IPacket`` and must be packed using our ``PACK`` cross-platform macro function.
Create an ``ECS::Network::PacketFactory`` to associate packet id to unserialization function. See our [example](#example).

### Client handler methods

- Start the client
```c++
void start(std::string &host, unsigned short port, ECS::Network::PacketFactory &factory)
```

- Setup packet reception
```c++
void onReceive(ECS::Network::ClientReceiveCallback callback)
```

- Send a packet without payload
```c++
void send(int8_t type)
```

- Send a packet with payload
```c++
template<typename Payload>
void send(int8_t type, Payload &payload)
```

- Stop the client
```c++
void stop()
```

### Server handler methods

- Start the server
```c++
void start(std::string &host, unsigned short port, unsigned short maxClients, PacketFactory &factory)
```

- Setup packet reception
```c++
void onReceive(ECS::Network::ServerReceiveCallback)
```

- Add a client
```c++
int addClient(size_t entityId)
```

- Get a client seat
```c++
int getClientSeat(size_t clientId)
```

- Remove a client
```c++
void removeClient(size_t clientId)
```

- Get current number of clients
```c++
int getNumberClients() const
```

- Send an error packet to a client
```c++
void sendError(unsigned short clientId)
```

- Send a packet to a client
```c++
template<typename Payload>
void send(PacketHeader &header, Payload &payload, unsigned short clientId, ECS::Core::SparseArray<Component::Connection> &connection)
```
```c++
template<typename Payload>
void send(int8_t type, Payload &payload, unsigned short clientId, ECS::Core::SparseArray<Component::Connection> &connection)
```

- Broadcast a packet
```c++
template<typename Payload>
void broadcast(int8_t type, Payload &payload, ECS::Core::SparseArray<Component::Connection> &connection)
```

- Broadcast a packet to all clients except one
```c++
template<typename Payload>
void broadcastExcept(int8_t type, Payload &payload, ECS::Core::SparseArray<Component::Connection> &connection, unsigned short excludedClientId)
``` 

- Check the server is full
```c++
int isFull()
``` 

- Stop the server
```c++
stop()
```

## Example

- Here is how to use our Network tool for a typical local server opened on port 4242, taking 100 players and receiving a move payload:

``ServerGamePackets.hpp``:
```c++
#include "EwECS/Network/Packet.hpp"

#ifndef SERVERGAMEPACKETS_HPP
    #define SERVERGAMEPACKETS_HPP

enum ServerGamePacketType = {
    CONNECT = 0,
    MOVE = 1,
    DISCONNECT = 2,
    MAX_SRV = 3
};

PACK(struct MovePayload
     : ECS::Network::IPayload {
         float moveX;
         float moveY;

         MovePayload() = default;

         MovePayload(float aMoveX, float aMoveY)
         {
             moveX = aMoveX;
             moveY = aMoveY;
         }
     });

static ECS::Network::PacketFactory packetFactory = {
    {GameEventType::MOVE, [](ECS::Network::Buffer &aBuffer) -> ECS::Network::IPayload * {
         return ECS::Network::unserializePointer<MovePayload>(aBuffer);
     }}};

#endif
```

``main.cpp``:
```c++
#include "EwECS/Network/Serialization.hpp"
#include "EwECS/Network/ServerHandler.hpp"
#include "ServerGamePackets.hpp"

int main()
{
    std::string host = "127.0.0.1";
    unsigned short port = 4242;
    unsigned short maxPlayers = 100;
    ECS::Network::ServerHandler &server = ECS::Network::ServerHandler::getInstance();

    server.onReceive([&server](int8_t aPacketType, ECS::Network::IPayload *aPayload, unsigned short aEntityId) {
        if (aPacketType >= ServerGamePacketType::MAX_SRV) {
            server.sendError(aEntityId);
            return;
        }
        if (aPacketType >= 0) {
            auto eventType = static_cast<ServerGamePacketType>(aPacketType);
            // process game actions (eg. triggering an EwECS event)
        } else if (aPacketType == AKNOWLEDGMENT_PACKET_TYPE) {
            // process aknowledgment actions (eg. triggering an EwECS event to check client connection status)
        }
    });
    server.start(host, port, maxPlayers, packetFactory);

    // ...
    // Add your components / systems / entities setup and game loop
    // ...

    server.stop();
    return 0;
}
```

- Here is how to use our Network tool for a typical client connecting to the server declared above:

``ClientGamePackets.hpp``:
```c++
#include "EwECS/Network/Packet.hpp"
#include "path/to/ServerGamePackets.hpp"

#ifndef CLIENTGAMEPACKETS_HPP
    #define CLIENTGAMEPACKETS_HPP

enum ClientGamePacketType = {
    // ...
    // MAX_CLI = ...
};

// ... define your payloads ...

static ECS::Network::PacketFactory packetFactory = {
    // ...
    // payload unserialiation
    // ...
};

#endif
```

``main.cpp``
```c++
int main()
{
        std::string host = "127.0.0.1";
        std::string port = 4242;
        auto &client = ECS::Network::ClientHandler::getInstance();

        client.onReceive([](int8_t aPacketType, ECS::Network::IPayload *aPayload) {
            if (aPacketType >= ClientGamePacket::MAX_CLI) {
                return;
            }
            if (aPacketType >= 0) {
                auto eventType = static_cast<RType::ClientEventType>(aPacketType);

                // process game actions (eg. triggering an EwECS event)
            }
        });

        client.start(host, port, RType::packetFactory);
        client.send(ServerGamePackets::CONNECT);

        // ...
        // Add your components / systems / entities setup and game loop
        // ...

        client.send(ServerGamePackets::DISCONNECT);
        client.stop();
        return 0;
}
```


