#pragma once

#include <SFML/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game;

class Events {
public:
  static bool checkMovingKeys(const sf::Keyboard::Scancode &lastKey,
                              const sf::Keyboard::Scancode &currentKey);
  static void handleEvents(Game &game);
};
