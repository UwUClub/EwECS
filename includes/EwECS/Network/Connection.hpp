#ifndef CONNECTION_COMPONENT_HPP
#define CONNECTION_COMPONENT_HPP

#include <string>

namespace ECS::Network {
    enum ConnectionStatus
    {
        PENDING,
        CONNECTED,
    };
}
namespace Component {
    struct Connection
    {
            /**
             * @brief Construct a new ConnectionStatus object
             *
             */
            Connection()
                : status(ECS::Network::ConnectionStatus::PENDING)
            {}
            /**
             * @brief Construct a new ConnectionStatus object
             *
             * @param aStatus The status of the entity
             */
            explicit Connection(ECS::Network::ConnectionStatus aStatus)
                : status(aStatus)
            {}

            ECS::Network::ConnectionStatus status;
            float age;
    };
} // namespace Component

#endif // EWECS_COMPONENTS_SOUND_HPP
