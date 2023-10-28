#include <iostream>
#include <strstream>
#include "Packet.hpp"

#ifndef SERIALIZATION_HPP
    #define SERIALIZATION_HPP

namespace ECS::Network {

    template<typename T>
    std::vector<uint8_t> serialize(T &data)
    {
        std::vector<uint8_t> bytes(sizeof(T));

        std::memcpy(bytes.data(), &data, sizeof(T));
        return bytes;
    }

    template<typename T>
    T unserialize(std::vector<uint8_t> &bytes)
    {
        T data;
        try {
            if (bytes.size() < sizeof(T)) {
                throw std::runtime_error("Invalid byte size for deserialization");
            }
            std::memcpy(&data, bytes.data(), sizeof(T));
        } catch (std::exception &e) {
            throw e;
        }
        return data;
    }

    template<typename T>
    IPayload *unserializePointer(std::vector<uint8_t> &bytes)
    {
        T *data = nullptr;
        try {
            if (bytes.size() != sizeof(T)) {
                throw std::runtime_error("Invalid byte size for deserialization");
            }
            data = new T;
            std::memcpy(data, bytes.data(), sizeof(T));
        } catch (std::exception &e) {
        }
        return data;
    }

} // namespace ECS::Network

#endif
