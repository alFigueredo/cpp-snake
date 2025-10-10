#pragma once

#include <SFML/Graphics/Font.hpp>
#include <random>

class RandomManager {
private:
  std::mt19937 gen;
  std::uniform_int_distribution<> randWidth;
  std::uniform_int_distribution<> randHeight;

public:
  RandomManager(const unsigned &width, const unsigned &height);
  int getWidth();
  int getHeight();
  sf::Vector2f getVector2f(const unsigned &size);
};
