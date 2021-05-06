/**
 * @file    Room.hpp
 * @brief   the dungeon definition
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

#ifndef DUNGEON_ADVENTURE_ROOM_H
#define DUNGEON_ADVENTURE_ROOM_H

#include <string>

/**
 * @brief dungeon adventure
 */
namespace dadv {

/**
 * @brief Rooms identifier
 */
using RoomId = unsigned long;

const RoomId InvalidDirection = -1;

/**
 * @brief A room inside the dungeon. It's connected to other rooms.
 */
struct Room {
  /**
   * @brief A unique identifier
   */
  RoomId id = 0;
  /**
   * @brief Description of the room
   */
  std::string description;
  /**
   * @brief Room id of the room at north
   */
  RoomId north = InvalidDirection;
  /**
   * @brief Room id of the room at east
   */
  RoomId east = InvalidDirection;
  /**
   * @brief Room id of the room at south
   */
  RoomId south = InvalidDirection;
  /**
   * @brief Room id of the room at west
   */
  RoomId west = InvalidDirection;
};

} // namespace dadv

#endif /* DUNGEON_ADVENTURE_ROOM_H */