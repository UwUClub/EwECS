add_subdirectory(Event)
add_subdirectory(SFMLDisplayClass)
add_subdirectory(ConfigReader)


target_sources(ecs PRIVATE
    World.cpp
    Utils.cpp
    )

target_link_libraries(ecs
        PRIVATE
        EwECS::EwECS_warnings
        sfml-graphics
        sfml-window
        sfml-system
        nlohmann_json
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ecs PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
