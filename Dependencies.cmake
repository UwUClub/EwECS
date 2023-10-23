include(cmake/CPM.cmake)
include(FetchContent)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(EwECS_setup_dependencies)

    # FetchContent_Declare(
    #     SFML
    #     GIT_REPOSITORY https://github.com/SFML/SFML.git
    #     GIT_TAG 2.6.0
    # )
    # FetchContent_MakeAvailable(SFML)

endfunction()
