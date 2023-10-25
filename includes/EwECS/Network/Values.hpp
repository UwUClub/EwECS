#include <iostream>

#ifndef NETWORK_VALUES_HPP
    #define NETWORK_VALUES_HPP

static constexpr int READ_BUFFER_SIZE = 1024;
static constexpr unsigned short MAX_NUMBER_PLAYER = 4;
static constexpr int8_t AKNOWLEDGMENT_PACKET_TYPE = -1;
static constexpr int8_t ERROR_PACKET_TYPE = -2;
static constexpr int8_t CONNECT_PACKET_TYPE = 0;
static constexpr int UUID_LENGTH = 36;

#endif
