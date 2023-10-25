add_subdirectory(Event)
add_subdirectory(SFMLDisplayClass)
add_subdirectory(ConfigReader)
add_subdirectory(Asset)
add_subdirectory(Sound)
add_subdirectory(Physic)

target_sources(ecs PRIVATE
    World.cpp
    Utils.cpp
    Logger.cpp
    )

target_link_libraries(ecs
        PUBLIC
        EwECS::EwECS_warnings
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        nlohmann_json
)

target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ecs PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
