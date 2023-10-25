add_subdirectory(Event)
add_subdirectory(SFMLDisplayClass)
add_subdirectory(ConfigReader)
add_subdirectory(Asset)
add_subdirectory(Components)
add_subdirectory(Sound)
add_subdirectory(Physic)

target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
