/**
 * @file    Explorer.cpp
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

#include "Explorer.hpp"
#include <stdexcept>

dadv::Explorer::Explorer(std::unique_ptr<Dungeon> dungeon, RoomId first,
                         RoomId last)
    : _dungeon(std::move(dungeon)), _position(first), _first(first),
      _last(last) {

  if (!_dungeon) {
    throw std::invalid_argument("Dungeon is a invalid pointer");
  }
}

dadv::Explorer::~Explorer() {}

std::string dadv::Explorer::getCurrentDescription() {
  auto it = _dungeon->find(_position);
  if (it == _dungeon->end()) {
    // Handle an invalid position
    return "";
  }
  return it->second.description;
}

std::string dadv::Explorer::getDirections() {
  auto it = _dungeon->find(_position);
  if (it == _dungeon->end()) {
    // Handle an invalid position
    return "";
  }
  std::string result("");
  if (_position->second.north != InvalidDirection) {
    result += "N - ";
  }
  if (_position->second.east != InvalidDirection) {
    result += "E - ";
  }
  if (_position->second.south != InvalidDirection) {
    result += "S - ";
  }
  if (_position->second.west != InvalidDirection) {
    result += "W - ";
  }
  if (result.length() > 0) {
    // Remove the last " - "
    return result.substr(0, result.length() - 3);
  }
  return result;
}

bool dadv::Explorer::goNorth() {
  auto it = _dungeon->find(_position);
  if (it == _dungeon->end()) {
    // Handle an invalid position
    return false;
  }
  return goToRoom(it->second.north);
}

bool dadv::Explorer::goEast() {
  auto it = _dungeon->find(_position);
  if (it == _dungeon->end()) {
    // Handle an invalid position
    return false;
  }
  return goToRoom(it->second.east);
}

bool dadv::Explorer::goSouth() {
  auto it = _dungeon->find(_position);
  if (it == _dungeon->end()) {
    // Handle an invalid position
    return false;
  }
  return goToRoom(it->second.south);
}

bool dadv::Explorer::goWest() {
  auto it = _dungeon->find(_position);
  if (it == _dungeon->end()) {
    // Handle an invalid position
    return false;
  }
  return goToRoom(it->second.west);
}

bool dadv::Explorer::isLastOne() {
  auto it = _dungeon->find(_position);
  if (it == _dungeon->end()) {
    // Handle an invalid position
    return false;
  }
  return it->first == _last;
}

bool dadv::Explorer::goToRoom(RoomId id) {
  if (id == InvalidDirection) {
    return false;
  }
  auto newRoom = _dungeon->find(id);
  if (newRoom == _dungeon->end()) {
    throw std::runtime_error("Room <" + std::to_string(id) +
                             "> doesn't exists");
  }
  _position = id;
  return true;
}
