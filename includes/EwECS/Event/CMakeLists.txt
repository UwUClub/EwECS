target_sources(ecs PUBLIC
    EventHandler.hpp
    EventManager.hpp
    KeyboardEvent.hpp
    WindowEvent.hpp
    MouseEvent.hpp
    SoundEvent.hpp
)

target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
