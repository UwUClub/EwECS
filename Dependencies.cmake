include(cmake/CPM.cmake)
include(FetchContent)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(EwECS_setup_dependencies)

    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0
    )
    FetchContent_MakeAvailable(SFML)

    if (NOT TARGET nlohmann_json)
    CPMAddPackage(
            NAME nlohmann_json
            VERSION 3.11.2
            GITHUB_REPOSITORY "nlohmann/json"
            GIT_TAG v3.11.2
            GIT_SHALLOW TRUE
    )
    endif()

endfunction()
