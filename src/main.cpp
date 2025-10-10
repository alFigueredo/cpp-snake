#include "game.hpp"

int main() {
  const std::string title = "Snake";
  Game &game = Game::initInstance("Snake");
  return 0;
}
