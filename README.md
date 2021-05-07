# Dungeon Adventure

A text-based game of dungeon exploration.

## How to run

``` bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build 
./build/code/bin/adventure
```

## How to play

The game describe a room and ask you to choose a direction.
You can choose North, South, East and West. Respond the first letter of the direction.
For example if you choose North write 'N'.

The objective is to arrive to the last room.

## Compile option

Is possible to run unit tests using the option ```ENABLE_TESTING```.
``` bash
cmake -S . -B build -DENABLE_TESTING=ON
cmake --build build 
cmake --build build --target test
```

Is possible run sanitizers too, setting option ```CMAKE_BUILD_TYPE``` to  ```TSAN```, ```ASAN```, ```LSAN``` and ```UBSAN```.
Some examples:
``` bash
cmake -S . -B build_asan -DCMAKE_BUILD_TYPE=asan -DENABLE_TESTING=ON
cmake --build build_asan
cmake --build build_asan --target test
./build_asan/code/bin/adventure
```

``` bash
cmake -S . -B build_ubsan -DCMAKE_BUILD_TYPE=ubsan -DENABLE_TESTING=ON
cmake --build build_ubsan 
cmake --build build_ubsan --target test
./build_ubsan/code/bin/adventure
```

``` bash
cmake -S . -B build_lsan -DCMAKE_BUILD_TYPE=lsan -DENABLE_TESTING=ON
cmake --build build_lsan 
cmake --build build_lsan --target test
./build_lsan/code/bin/adventure

```

Attention! Asan detect some errors on catch2. They are out of the control of this project.


## Other information

The project has been tested only on linux.