#pragma once

#include <SFML/Window/Keyboard.hpp>

class Game;

class Events {
public:
  static void handleEvents(Game &game);
};
