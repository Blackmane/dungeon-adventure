/**
 * @file    Explorer.hpp
 * @brief   explorer permits to move inside a dungeon
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

#ifndef DUNGEON_ADVENTURE_EXPLORER_H
#define DUNGEON_ADVENTURE_EXPLORER_H

#include "Room.hpp"
#include <memory>
#include <unordered_map>

/**
 * @brief dungeon adventure
 */
namespace dadv {

/**
 * @brief Dungeon is a "set" of connected rooms.
 */
using Dungeon = std::unordered_map<RoomId, Room>;

/**
 * @brief Explorer permits to move inside a Dungeon.
 */
class Explorer {

public:
  /**
   * @brief Create an explorer
   * @param dungeon unique reference to a dungeon. Dungeon should not empty.
   * @param first room from where explorer start
   * @param last room to arrive
   */
  explicit Explorer(std::unique_ptr<Dungeon> dungeon, const RoomId first,
                    const RoomId last);
  /**
   * @brief Destructor
   */
  ~Explorer() = default;

  /**
   * @brief Get the description of the current room
   * @return the description
   */
  std::string getCurrentDescription() noexcept;
  /**
   * @brief Get a ordered list of the possible directions.
   * List is like "NESW" if all directions are valid.
   * "EW" only if East and West are valid.
   * "S" only if South is valid.
   * Empty string if none are valid.
   * @return list of direction
   */
  std::string getDirections() noexcept;

  /**
   * @brief Move position to North, if is valid.
   * @return true if it was a valid move
   */
  bool goNorth();
  /**
   * @brief Move position to East, if is valid.
   * @return true if it was a valid move
   */
  bool goEast();
  /**
   * @brief Move position to South, if is valid.
   * @return true if it was a valid move
   */
  bool goSouth();
  /**
   * @brief Move position to West, if is valid.
   * @return true if it was a valid move
   */
  bool goWest();

  /**
   * @brief Return if current room is the last one
   * @return if is the last room
   */
  bool isLastOne() noexcept;

private:
  /**
   * @brief Move position to a specific room id
   * @return if is was a valid move
   */
  bool goToRoom(const RoomId id);

  /**
   * @brief Dungeon rappresentation
   */
  const std::unique_ptr<Dungeon> _dungeon;
  /**
   * @brief Current room id
   */
  Dungeon::iterator _position;
  /**
   * @brief Last room id
   */
  const RoomId _last;
};

} // namespace dadv

#endif /* DUNGEON_ADVENTURE_EXPLORER_H */