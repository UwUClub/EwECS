add_subdirectory(Event)
add_subdirectory(SFMLDisplayClass)
add_subdirectory(ConfigReader)
add_subdirectory(Asset)
add_subdirectory(Sound)
add_subdirectory(Physic)
add_subdirectory(Network)

target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
