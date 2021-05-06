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
