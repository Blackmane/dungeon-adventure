/**
 * @file    game_test.cpp
 * @brief   test suite for game
 *
 * @author  Niccolò Pieretti
 * @date    07 Mag 2021
 *
 ****************************************************************************
 *
 *             _  _   o   __  __   __    _  o   _   ,_    _
 *            / |/ |  |  /   /    /  \_|/ \_|  |/  /  |  |/
 *              |  |_/|_/\__/\___/\__/ |__/ |_/|__/   |_/|__/
 *                                    /|
 *                                    \|
 ****************************************************************************/

#include "Explorer.hpp"
#include "Game.hpp"
#include "Room.hpp"
#include "catch.hpp"

#include <memory>
#include <sstream>

TEST_CASE("Test Game utils", "[game]") {

  SECTION("Invalid path") {
    dadv::RoomId first, last;
    REQUIRE_THROWS_AS(dadv::getDungeonFromFile("", &first, &last),
                      std::invalid_argument);
    REQUIRE_THROWS_AS(
        dadv::getDungeonFromFile("invalid/path/to/map.dat", &first, &last),
        std::invalid_argument);
  }

  SECTION("Empty dungeon") {
    dadv::RoomId first, last;
    auto dungeon =
        dadv::getDungeonFromFile("worlds/emptyMap.dat", &first, &last);
    REQUIRE(dungeon->size() == 0);
  }

  SECTION("One room dungeon") {
    dadv::RoomId first, last;
    auto dungeon =
        dadv::getDungeonFromFile("worlds/oneRoom.dat", &first, &last);
    REQUIRE(dungeon->size() == 1);
    REQUIRE(dungeon->at(0).id == 0);
    REQUIRE(dungeon->at(0).description == "Empty room");
    REQUIRE(dungeon->at(0).north == dadv::InvalidDirection);
    REQUIRE(dungeon->at(0).east == dadv::InvalidDirection);
    REQUIRE(dungeon->at(0).south == dadv::InvalidDirection);
    REQUIRE(dungeon->at(0).west == dadv::InvalidDirection);
  }

  SECTION("Multiple room dungeon") {
    dadv::RoomId first, last;
    auto dungeon =
        dadv::getDungeonFromFile("worlds/multipleRoom.dat", &first, &last);
    REQUIRE(dungeon->size() == 3);
    REQUIRE(dungeon->at(0).id == 0);
    REQUIRE(dungeon->at(0).description != "");
    REQUIRE(dungeon->at(0).north == dadv::InvalidDirection);
    REQUIRE(dungeon->at(0).east == 1);
    REQUIRE(dungeon->at(0).south == dadv::InvalidDirection);
    REQUIRE(dungeon->at(0).west == dadv::InvalidDirection);
    REQUIRE(dungeon->at(1).id == 1);
    REQUIRE(dungeon->at(1).description != "");
    REQUIRE(dungeon->at(1).north == dadv::InvalidDirection);
    REQUIRE(dungeon->at(1).east == dadv::InvalidDirection);
    REQUIRE(dungeon->at(1).south == 99);
    REQUIRE(dungeon->at(1).west == 0);
    REQUIRE(dungeon->at(99).id == 99);
    REQUIRE(dungeon->at(99).description != "");
    REQUIRE(dungeon->at(99).north == dadv::InvalidDirection);
    REQUIRE(dungeon->at(99).east == dadv::InvalidDirection);
    REQUIRE(dungeon->at(99).south == dadv::InvalidDirection);
    REQUIRE(dungeon->at(99).west == dadv::InvalidDirection);
  }
}

TEST_CASE("Create a Game", "[game]") {

  SECTION("Invalid explorer") {
    std::unique_ptr<dadv::Explorer> explorer;
    REQUIRE_THROWS_AS(dadv::Game(std::move(explorer)), std::invalid_argument);
  }

  SECTION("Valid explorer from dat file") {
    dadv::RoomId first, last;
    std::unique_ptr<dadv::Explorer> explorer =
        std::unique_ptr<dadv::Explorer>(new dadv::Explorer(
            dadv::getDungeonFromFile("worlds/oneRoom.dat", &first, &last),
            first, last));
    dadv::Game game(std::move(explorer));
  }

  SECTION("Create game using loadFromMap") {
    auto game = dadv::Game::loadFromMap("worlds/oneRoom.dat");
    std::ostringstream oss;
    std::istringstream iss("\n");
    game->start(oss, iss);
    REQUIRE(oss);
    REQUIRE(oss.str() == "Empty room\n");
  }
}
