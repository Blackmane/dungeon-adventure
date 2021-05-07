/**
 * @file    adventure.cpp
 * @brief   textual dungeon adventure
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

#include "Game.hpp"

#include <string>

const std::string WorldPath = "worlds/world.dat";

int main(void) {

    auto game = dadv::Game::loadFromMap(WorldPath);
    game->start();

  return 0;
}