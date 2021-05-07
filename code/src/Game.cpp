/**
 * @file    Game.cpp
 * @brief   implementation
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

#include "Game.hpp"

#include <fstream>
#include <iostream>

#define READ_LINE(source, line, name, line_count)                              \
  {                                                                            \
    if (!std::getline(source, line, '\n')) {                                   \
      throw std::runtime_error("Malformed room on line " +                     \
                               std::to_string(line_count) + " (" + name +      \
                               ")");                                           \
    }                                                                          \
    line_count++;                                                              \
  }

std::unique_ptr<dadv::Dungeon>
dadv::getDungeonFromFile(const std::string pathToFile, RoomId *const first,
                         RoomId *const last) {
  // Check arguments
  if (pathToFile == "") {
    throw std::invalid_argument("Empty path to file");
  }
  if (!first) {
    throw std::invalid_argument("First is a nullpointer");
  }
  if (!last) {
    throw std::invalid_argument("last is a nullpointer");
  }

  std::unique_ptr<dadv::Dungeon> dungeon =
      std::unique_ptr<dadv::Dungeon>(new Dungeon());

  // Open file
  std::ifstream source;
  source.open(pathToFile);
  if (!source.good()) {
    throw std::invalid_argument("Invalid path to file");
  }

  int i = 0;
  bool readAll = false;
  std::string id;
  if (!std::getline(source, id, '\n')) {
    // File is empty
    readAll = true;
  } else {
    // File is not empty: Id is a valid value
    try {
      *first = std::stoi(id);
    } catch (std::exception &e) {
      throw std::runtime_error("Malformed room on line " + std::to_string(i));
    }
  }
  while (!readAll) {
    Room room;
    try {
      room.id = std::stoi(id);
      *last = room.id;
      i++; // Count id as read
      std::string description;
      READ_LINE(source, description, "description", i);
      room.description = description;
      std::string north;
      READ_LINE(source, north, "north", i);
      room.north = std::stoi(north);
      std::string south;
      READ_LINE(source, south, "south", i);
      room.south = std::stoi(south);
      std::string east;
      READ_LINE(source, east, "east", i);
      room.east = std::stoi(east);
      std::string west;
      READ_LINE(source, west, "west", i);
      room.west = std::stoi(west);

      dungeon->emplace(std::pair<RoomId, Room>(room.id, room));
      std::string dashes;
      std::getline(source, dashes, '\n');
    } catch (std::runtime_error &e) {
      throw e;
    } catch (std::exception &e) {
      throw std::runtime_error("Malformed room on line " + std::to_string(i));
    }
    if (!std::getline(source, id, '\n')) {
      readAll = true;
    }
  }
  return dungeon;
}

dadv::Game::Game(std::unique_ptr<Explorer> explorer)
    : _explorer(std::move(explorer)) {

  if (!_explorer) {
    throw std::invalid_argument("Explorer is an invalid pointer");
  }
}

void dadv::Game::start(std::ostream &os, std::istream &is) {
  os << _explorer->getCurrentDescription() << std::endl;
  while (!_explorer->isLastOne()) {
    bool isResponseCorrect = false;
    do {
      os << "Dove vuoi andare [" << _explorer->getDirections() << "] ?"
         << std::endl;
      std::string input;
      is >> input;
      switch (input[0]) {
      case 'N':
      case 'n':
        isResponseCorrect = _explorer->goNorth();
        break;
      case 'S':
      case 's':
        isResponseCorrect = _explorer->goSouth();
        break;
      case 'E':
      case 'e':
        isResponseCorrect = _explorer->goEast();
        break;
      case 'W':
      case 'w':
        isResponseCorrect = _explorer->goWest();
        break;
      default:
        break;
      }
      if (!isResponseCorrect) {
        os << "Non puoi" << std::endl;
      }
    } while (!isResponseCorrect);
    os << _explorer->getCurrentDescription() << std::endl;
  }
}

std::unique_ptr<dadv::Game>
dadv::Game::loadFromMap(const std::string pathToMap) {
  dadv::RoomId first, last;
  std::unique_ptr<dadv::Explorer> explorer =
      std::unique_ptr<dadv::Explorer>(new dadv::Explorer(
          dadv::getDungeonFromFile(pathToMap, &first, &last), first,
          last));
  return std::unique_ptr<Game>(new Game(std::move(explorer)));
}
