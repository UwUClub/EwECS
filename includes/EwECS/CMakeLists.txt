add_subdirectory(Event)

target_sources(ecs PUBLIC
    EwECS.hpp
    SparseArray.hpp
    Utils.hpp
    World.hpp
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
