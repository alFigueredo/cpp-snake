#include "game.hpp"

int main() {
  const std::string title = "Snake";
  Game &game = Game::initInstance(title);
  game.run();
  return 0;
}
