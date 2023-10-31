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

## Handlers

The Network is composed of 3 singleton handlers: ``NetworkHandler``, ``ClientHandler`` and ``ServerHandler``.
``NetworkHandler`` defines common basis features used by client and server, such as packet send / reception.

When using our Network tool you must define a struct for each packet payload. Those struct inherit from ``IPacket`` and must be packed properly.
Create an ``ECS::Network::PacketFactory`` to associate packet id to unserialization function. See our [example](#example).

### Client handler methods

- Start the client
```c++
void start(std::string &host, unsigned short port, unsigned short maxClients, ECS::Network::PacketFactory &factory)
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

- Start the client
```c++
void start(std::string &host, unsigned short port, PacketFactory &factory)
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



