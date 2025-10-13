#pragma once

#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game;

class Events {
public:
  static void handleEvents(Game &game);
};
