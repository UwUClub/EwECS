add_subdirectory(Event)
add_subdirectory(SFMLDisplayClass)
add_subdirectory(ConfigReader)
add_subdirectory(Asset)

target_sources(ecs PUBLIC
    EwECS.hpp
    SparseArray.hpp
    Utils.hpp
    World.hpp
    IPlugin.hpp
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
