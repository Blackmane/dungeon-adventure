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
        # $<$<NOT:$<CONFIG:DEBUG>>:-O2> 
        "$<$<CONFIG:TSAN>:-fsanitize=thread;-g;-O1>"
        "$<$<CONFIG:ASAN>:-fsanitize=address;-fno-optimize-sibling-calls;-fsanitize-address-use-after-scope;-fno-omit-frame-pointer;-g;-O1>"
        "$<$<CONFIG:LSAN>:-fsanitize=leak;-fno-omit-frame-pointer;-g;-O1>"
        # "$<$<CONFIG:MSAN>:-fsanitize=memory;-fno-optimize-sibling-calls;-fsanitize-memory-track-origins=2;-fno-omit-frame-pointer;-g;-O2>"
        "$<$<CONFIG:UBSAN>:-fsanitize=undefined>"
        -fPIC)

    add_link_options(
        $<$<CONFIG:TSAN>:-fsanitize=thread> 
        $<$<CONFIG:ASAN>:-fsanitize=address>
        $<$<CONFIG:TSAN>:-fsanitize=leak>
        #$<$<CONFIG:MSAN>:-fsanitize=memory>
        $<$<CONFIG:UBSAN>:-fsanitize=undefined> 
        )

    # Adding an option to switch on or off compilation of tests
    option (ENABLE_TESTING "Set to ON to perform unit tests" OFF)
    if (ENABLE_TESTING)
        enable_testing()
        add_subdirectory(tests)
    endif ()

endif()


add_subdirectory (code)