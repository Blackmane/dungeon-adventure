/**
 * @file    explorer_test.cpp
 * @brief   test suite for explorer
 *
 * @author  Niccolò Pieretti
 * @date    06 Mag 2021
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
#include "catch.hpp"

#include <cstring>
#include <memory>

TEST_CASE("Test Explorer", "[explorer]") {

  SECTION("Empty dungeon") {
    std::unique_ptr<dadv::Dungeon> dungeon;
    REQUIRE_THROWS_AS(new dadv::Explorer(std::move(dungeon), 0, 0),
                      std::invalid_argument);
    dungeon = std::unique_ptr<dadv::Dungeon>(new dadv::Dungeon());
    auto explorer = new dadv::Explorer(std::move(dungeon), 0, 0);
    REQUIRE(explorer->getCurrentDescription() == description);
    REQUIRE_THROWS_AS(explorer->goNorth(), std::runtime_error);
    REQUIRE_THROWS_AS(explorer->goEast(), std::runtime_error);
    REQUIRE_THROWS_AS(explorer->goSouth(), std::runtime_error);
    REQUIRE_THROWS_AS(explorer->goWest(), std::runtime_error);
    REQUIRE(explorer->getDirections() == "N - E - S - W");
    REQUIRE(explorer->isLastOne());
  }

  SECTION("One room dungeon") {
    std::unique_ptr<dadv::Dungeon> dungeon =
        std::unique_ptr<dadv::Dungeon>(new dadv::Dungeon());
    std::string description("An empty room, how did you get in here?");
    dadv::Room emptyRoom;
    emptyRoom.description = description;
    dungeon->emplace(
        std::pair<dadv::RoomId, dadv::Room>(emptyRoom.id, emptyRoom));
    auto explorer = new dadv::Explorer(std::move(dungeon), 0, 0);
    REQUIRE(explorer->getCurrentDescription() == description);
    REQUIRE_FALSE(explorer->goNorth());
    REQUIRE_FALSE(explorer->goEast());
    REQUIRE_FALSE(explorer->goSouth());
    REQUIRE_FALSE(explorer->goWest());
    REQUIRE(explorer->isLastOne());
    REQUIRE(explorer->getDirections() == "");
  }

  SECTION("More rooms dungeon") {
    std::unique_ptr<dadv::Dungeon> dungeon =
        std::unique_ptr<dadv::Dungeon>(new dadv::Dungeon());
    dadv::Room room;
    // Build dungeon rooms
    std::string descriptionA("First room");
    room.id = 0;
    room.description = descriptionA;
    room.south = 1;
    dungeon->emplace(std::pair<dadv::RoomId, dadv::Room>(room.id, room));
    room.south = dadv::InvalidDirection;
    std::string descriptionB("Middle room");
    room.id = 1;
    room.description = descriptionB;
    room.east = 2;
    room.north = 0;
    dungeon->emplace(std::pair<dadv::RoomId, dadv::Room>(room.id, room));
    room.east = dadv::InvalidDirection;
    room.north = dadv::InvalidDirection;
    std::string descriptionC("Last room");
    room.id = 2;
    room.description = descriptionC;
    room.west = 1;
    dungeon->emplace(std::pair<dadv::RoomId, dadv::Room>(room.id, room));
    // Start adventure
    auto explorer = new dadv::Explorer(std::move(dungeon), 0, 2);
    // First room (A)
    REQUIRE(explorer->getCurrentDescription() == descriptionA);
    REQUIRE_FALSE(explorer->isLastOne());
    REQUIRE_FALSE(explorer->goNorth());
    REQUIRE_FALSE(explorer->goEast());
    REQUIRE_FALSE(explorer->goWest());
    REQUIRE(explorer->getDirections() == "S");
    REQUIRE(explorer->goSouth());
    // Second room (B)
    REQUIRE(explorer->getCurrentDescription() == descriptionB);
    REQUIRE_FALSE(explorer->isLastOne());
    REQUIRE(explorer->getDirections() == "N - E");
    REQUIRE(explorer->goNorth());
    // Back to first room (A)
    REQUIRE(explorer->getCurrentDescription() == descriptionA);
    REQUIRE(explorer->goSouth());
    // Second room (B)
    REQUIRE(explorer->getCurrentDescription() == descriptionB);
    REQUIRE_FALSE(explorer->goSouth());
    REQUIRE_FALSE(explorer->goWest());
    REQUIRE(explorer->goEast());
    // Last room (C)
    REQUIRE(explorer->getCurrentDescription() == descriptionC);
    REQUIRE(explorer->isLastOne());
    REQUIRE(explorer->getDirections() == "W");
    REQUIRE_FALSE(explorer->goNorth());
    REQUIRE_FALSE(explorer->goEast());
    REQUIRE_FALSE(explorer->goSouth());
    REQUIRE(explorer->goWest());
    // Second room (B)
    REQUIRE(explorer->goNorth());
    // First room (A)
    REQUIRE(explorer->getCurrentDescription() == descriptionA);
  }
}