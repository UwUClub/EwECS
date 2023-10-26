target_sources(ecs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/PhysicPlugin.cpp
    )

target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
