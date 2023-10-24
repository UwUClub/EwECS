target_sources(ecs PUBLIC
    PhysicPlugin.hpp
    HitBox.hpp
    Weight.hpp
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
