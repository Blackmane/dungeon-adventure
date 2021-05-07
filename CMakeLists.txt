cmake_minimum_required(VERSION 3.11)

project(dungeon_adventure
    VERSION 0.1
    DESCRIPTION "A text-based game of dungeon exploration."
    )

if (ENABLE_TESTING AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    # https://interrupt.memfault.com/blog/best-and-worst-gcc-clang-compiler-flags
    add_compile_options(
        -Wall -Wextra -Wno-unused-parameter 
        -pedantic 
        -Wshadow -Wdouble-promotion
        -Wformat=2 -Wformat-truncation
        -ffunction-sections -fdata-sections
        -pie
        "$<$<CONFIG:RELEASE>:-Werror;-g3;-O2>"
        -fPIC)
    # Adding an option to switch on or off compilation of tests
    option (ENABLE_TESTING "Set to ON to perform unit tests" OFF)
    if (ENABLE_TESTING)
        enable_testing()
        add_subdirectory(tests)
    endif ()

endif()


add_subdirectory (code)