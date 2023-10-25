add_subdirectory(Event)
add_subdirectory(SFMLDisplayClass)
add_subdirectory(ConfigReader)
add_subdirectory(Asset)
add_subdirectory(Components)
add_subdirectory(Sound)
add_subdirectory(Physic)

target_sources(ecs
    PRIVATE
    EwECS.hpp
    SparseArray.hpp
    Utils.hpp
    World.hpp
    IPlugin.hpp
)

target_link_libraries(ecs
        PRIVATE
        EwECS::EwECS_warnings
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        nlohmann_json
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
