# ===== ===== ===== Source code ===== ===== ===== 

set(DADVENTURE_HEADER_LIST 
    "${dungeon_adventure_SOURCE_DIR}/code/include/Room.hpp"
    "${dungeon_adventure_SOURCE_DIR}/code/include/Explorer.hpp"
    "${dungeon_adventure_SOURCE_DIR}/code/include/Game.hpp"
    )

set(DADVENTURE_SRC_LIST 
    "${dungeon_adventure_SOURCE_DIR}/code/src/Explorer.cpp"
    "${dungeon_adventure_SOURCE_DIR}/code/src/Game.cpp"
    )


# ===== ===== ===== Samples ===== ===== 

# adventure
add_executable (adventure 
    ${DADVENTURE_HEADER_LIST} 
    ${DADVENTURE_SRC_LIST}
    samples/adventure.cpp )
target_include_directories(adventure PRIVATE include/)
target_compile_features(adventure PRIVATE cxx_std_11)
