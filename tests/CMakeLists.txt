# ===== ===== ===== Main Obj ===== ===== ===== 
add_library(MAIN_objs OBJECT main_catch.cpp)
target_compile_features(MAIN_objs PUBLIC cxx_std_11)

# ===== ===== ===== Tests ===== ===== ===== 

# ~~~~~ ~~~~~ Explorer test ~~~~~ ~~~~~ 
add_executable(explorerTest 
    $<TARGET_OBJECTS:MAIN_objs>
    explorer_test.cpp
    "${dungeon_adventure_SOURCE_DIR}/code/include/Room.hpp"
    "${dungeon_adventure_SOURCE_DIR}/code/include/Explorer.hpp"
    "${dungeon_adventure_SOURCE_DIR}/code/src/Explorer.cpp"
    )

target_compile_features(explorerTest PRIVATE cxx_std_11)
target_include_directories(explorerTest PRIVATE ../code/include)

add_test(NAME testexplorer COMMAND explorerTest)


# ~~~~~ ~~~~~ Game test ~~~~~ ~~~~~ 
add_executable(gameTest 
    $<TARGET_OBJECTS:MAIN_objs>
    game_test.cpp
    "${dungeon_adventure_SOURCE_DIR}/code/include/Room.hpp"
    "${dungeon_adventure_SOURCE_DIR}/code/include/Explorer.hpp"
    "${dungeon_adventure_SOURCE_DIR}/code/include/Game.hpp"
    "${dungeon_adventure_SOURCE_DIR}/code/src/Explorer.cpp"
    "${dungeon_adventure_SOURCE_DIR}/code/src/Game.cpp"
    )

target_compile_features(gameTest PRIVATE cxx_std_11)
target_include_directories(gameTest PRIVATE ../code/include)

add_test(NAME testgame COMMAND gameTest)

# Copy worlds to build directory
make_directory(${CMAKE_CURRENT_BINARY_DIR}/worlds)
add_custom_command(
    TARGET gameTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${dungeon_adventure_SOURCE_DIR}/worlds/*.dat
            ${CMAKE_CURRENT_BINARY_DIR}/worlds)
make_directory(${CMAKE_CURRENT_BINARY_DIR}/bin/worlds)
# Workaround: launch tests from main directory
add_custom_command(
    TARGET gameTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${dungeon_adventure_SOURCE_DIR}/worlds/*.dat
            ${CMAKE_CURRENT_BINARY_DIR}/bin/worlds)
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${CMAKE_CURRENT_BINARY_DIR})