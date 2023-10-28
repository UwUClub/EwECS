target_sources(ecs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ServerHandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ClientHandler.cpp
    )

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
