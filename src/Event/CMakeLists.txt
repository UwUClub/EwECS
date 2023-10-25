target_sources(ecs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/EventManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KeyboardEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MouseEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/WindowEvent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SoundEvent.cpp
    )

target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
