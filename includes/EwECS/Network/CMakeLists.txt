target_sources(ecs PUBLIC
    ClientHandler.hpp
    ServerHandler.hpp
    NetworkHandler.hpp
    Packet.hpp
    Serialization.hpp
    Values.hpp
    Connection.hpp
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
