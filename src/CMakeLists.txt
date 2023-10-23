add_subdirectory(Event)
add_subdirectory(Asset)

target_sources(ecs PRIVATE
    World.cpp
    Utils.cpp
    )

target_link_libraries(ecs
        PRIVATE
        EwECS::EwECS_warnings
)

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(ecs PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
