include(FetchContent)

# Done as a function so that updates to variables like
# CMAKE_CXX_FLAGS don't propagate out to other
# targets
function(EwECS_setup_dependencies)

    set(BOOST_VERSION "1.83.0")
    set(BOOST_LIBS system serialization align assert config core static_assert throw_exception array bind chrono integer move mpl predef asio ratio type_traits typeof utility coroutine date_time function regex smart_ptr preprocessor io uuid)
    set(BOOST_INCLUDE_LIBRARIES ${BOOST_LIBS})

    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(FETCHCONTENT_QUIET FALSE)

    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.0
    )
    FetchContent_MakeAvailable(SFML)

    FetchContent_Declare(
            nlohmann_json
            GIT_REPOSITORY https://github.com/nlohmann/json.git
            GIT_TAG v3.11.2
    )
    FetchContent_MakeAvailable(nlohmann_json)

    FetchContent_Declare(
            Boost
            URL https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION}/boost-${BOOST_VERSION}.7z
            USES_TERMINAL_DOWNLOAD TRUE
            GIT_PROGRESS TRUE
            DOWNLOAD_NO_EXTRACT FALSE
    )
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)
    FetchContent_MakeAvailable(Boost)

endfunction()
