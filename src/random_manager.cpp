#include "random_manager.hpp"

RandomManager::RandomManager(const unsigned &width, const unsigned &height)
    : randWidth(std::uniform_int_distribution<>(0, width - 1)),
      randHeight(std::uniform_int_distribution<>(0, height - 1)) {
  std::random_device rd;
  gen = std::mt19937(rd());
}

int RandomManager::getWidth() { return randWidth(gen); }

int RandomManager::getHeight() { return randHeight(gen); }

sf::Vector2i RandomManager::getVector2() {
  return sf::Vector2i(getWidth(), getHeight());
}
