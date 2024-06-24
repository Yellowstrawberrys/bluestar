
# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()


# tmx
find_package(tmx QUIET)
if (NOT tmx_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            tmx
            GIT_REPOSITORY https://github.com/baylej/tmx.git
            GIT_TAG 11ffdcd
    )
    FetchContent_GetProperties(tmx)
    if (NOT tmx_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(tmx)
        add_subdirectory(${tmx_SOURCE_DIR} ${tmx_BINARY_DIR})
    endif()
endif()

find_package(raylib-tmx QUIET)
if (NOT raylib-tmx_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib-tmx
            GIT_REPOSITORY https://github.com/RobLoach/raylib-tmx.git
            GIT_TAG 45a2a16
    )
    FetchContent_GetProperties(raylib-tmx)
    if (NOT raylib-tmx_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib-tmx)
        add_subdirectory(${raylib-tmx_SOURCE_DIR} ${raylib-tmx_BINARY_DIR})
    endif()
endif()