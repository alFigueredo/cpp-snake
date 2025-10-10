#include "game.hpp"

Game::Game(const std::string &title_)
    : title(title_), window(std::make_unique<Window>(title)) {
  reset();
}

Game &Game::initInstance(const std::string &title) {
  static Game game(title);
  return game;
}

unsigned Game::getScore() const { return score; }
sf::Keyboard::Scancode Game::getMoving() const { return moving; }
unsigned Game::getBaseTime() const { return baseTime; }
bool Game::getLose() const { return lose; }
bool Game::getPaused() const { return paused; }
Window &Game::getWindow() const { return *window; }

void Game::setScore(const unsigned &score) { this->score = score; }
void Game::setMoving(const sf::Keyboard::Scancode &moving) {
  this->moving = moving;
}
void Game::setTimeGap(const unsigned &timeGap) { this->timeGap = timeGap; }
void Game::setLose(const bool &lose) { this->lose = lose; }
void Game::setPaused(const bool &paused) { this->paused = paused; }

void Game::reset() {
  setScore(0);
  setMoving(sf::Keyboard::Scancode::D);
  setTimeGap(baseTime);
  setLose(false);
  setPaused(false);
  getWindow().reset(score);
}

void Game::run() { Events::handleEvents(*this); }

void Game::move() {
  switch (moving) {
  case sf::Keyboard::Scancode::W:
    getWindow().moveSnake(sf::Vector2f(0, -1));
    break;
  case sf::Keyboard::Scancode::S:
    getWindow().moveSnake(sf::Vector2f(0, 1));
    break;
  case sf::Keyboard::Scancode::A:
    getWindow().moveSnake(sf::Vector2f(-1, 0));
    break;
  case sf::Keyboard::Scancode::D:
    getWindow().moveSnake(sf::Vector2f(1, 0));
    break;
  default:
    break;
  }
}

void Game::lost() {
  window->lose(getScore());
  setLose(true);
}

void Game::pause() {
  window->pause();
  setPaused(true);
}

void Game::close() {
  window->close();
  exit(0);
}

bool Game::isOpen() const { return getWindow().isOpen(); }
