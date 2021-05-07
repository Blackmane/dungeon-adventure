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

dadv::Explorer::Explorer(std::unique_ptr<Dungeon> dungeon, const RoomId first,
                         const RoomId last)
    : _dungeon(std::move(dungeon)), _last(last) {

  if (!_dungeon) {
    throw std::invalid_argument("Dungeon is an invalid pointer");
  }

  _position = _dungeon->find(first);
  if (_position == _dungeon->end()) {
    throw std::invalid_argument("First room doesn't exist");
  }
}

std::string dadv::Explorer::getCurrentDescription() noexcept {
  return _position->second.description;
}

std::string dadv::Explorer::getDirections() noexcept {
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

bool dadv::Explorer::goNorth() { return goToRoom(_position->second.north); }

bool dadv::Explorer::goEast() { return goToRoom(_position->second.east); }

bool dadv::Explorer::goSouth() { return goToRoom(_position->second.south); }

bool dadv::Explorer::goWest() { return goToRoom(_position->second.west); }

bool dadv::Explorer::isLastOne() noexcept { return _position->first == _last; }

bool dadv::Explorer::goToRoom(const RoomId id) {
  if (id == InvalidDirection) {
    return false;
  }
  auto newRoom = _dungeon->find(id);
  if (newRoom == _dungeon->end()) {
    throw std::runtime_error("Room <" + std::to_string(id) +
                             "> doesn't exists");
  }
  _position = newRoom;
  return true;
}