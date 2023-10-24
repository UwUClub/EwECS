target_sources(ecs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SFMLDisplayClass.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderPlugin.cpp
    )

target_include_directories(ecs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
