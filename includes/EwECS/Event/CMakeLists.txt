target_sources(ecs PUBLIC
    EventHandler.hpp
    EventManager.hpp
    KeyboardEvent.hpp
    WindowEvent.hpp
    MouseEvent.hpp
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
