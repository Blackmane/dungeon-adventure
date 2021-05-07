/**
 * @file    Game.hpp
 * @brief   game permits to play to dungeon adventure
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

#ifndef DUNGEON_ADVENTURE_GAME_H
#define DUNGEON_ADVENTURE_GAME_H

#include "Explorer.hpp"
#include "Room.hpp"
#include <iostream>
#include <memory>
#include <string>

/**
 * @brief dungeon adventure
 */
namespace dadv {

/**
 * @brief Create a dungeon from a dat file
 * @param pathToFile a valid path to dat file
 * @param first is a pointer where to save the first room id
 * @param last is a pointer where to save the last room id
 * @throw invalid_argument if path is invalid
 * @throw runtime_error if file is malformed
 */
std::unique_ptr<Dungeon> getDungeonFromFile(const std::string pathToFile,
                                            RoomId *const first,
                                            RoomId *const last);

/**
 * @brief Game permits to play to dungeon adventure
 */
class Game {

public:
  /**
   * @brief Create a new game
   * @param explorer unique reference to an explorer
   * @throw invalid_argument if explorer is an invalid pointer
   */
  explicit Game(std::unique_ptr<Explorer> explorer);

  /**
   * @brief Destructor
   */
  ~Game() = default;

  /**
   * @brief Start the game
   * @param os stream to redirect output
   * @param is stream from get input
   */
  void start(std::ostream &os = std::cout, std::istream &is = std::cin);

  /**
   * @brief Create a new Game from a file
   * @param pathToMap path to file
   * @return unique pointer to a new Game
   */
  static std::unique_ptr<Game> loadFromMap(const std::string pathToMap);

private:
  /**
   * @brief explorer reference
   */
  std::unique_ptr<Explorer> _explorer;
};

} // namespace dadv

#endif /* DUNGEON_ADVENTURE_GAME_H */