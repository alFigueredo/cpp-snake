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
sf::Keyboard::Scancode Game::getLastMoving() const { return lastMoving; }
unsigned Game::getBaseTime() const { return baseTime; }
unsigned Game::getBaseLimit() const { return baseLimit; }
unsigned Game::getBaseGap() const { return baseGap; }
unsigned Game::getTimeGap() const { return timeGap; }
bool Game::isLose() const { return lose; }
bool Game::isPaused() const { return paused; }
bool Game::isRunning() const { return !isLose() && !isPaused(); }
Window &Game::getWindow() const { return *window; }

void Game::setScore(const unsigned &score) { this->score = score; }
void Game::setMoving(const sf::Keyboard::Scancode &moving) {
  this->moving = moving;
}
void Game::setLastMoving() { lastMoving = moving; }
void Game::setTimeGap(const unsigned &timeGap) { this->timeGap = timeGap; }
void Game::setLose(const bool &lose) { this->lose = lose; }
void Game::setPaused(const bool &paused) { this->paused = paused; }
void Game::reduceTimeGap() {
  if (getTimeGap() > getBaseLimit() * 2)
    setTimeGap(getTimeGap() - getBaseGap());
}

void Game::reset() {
  setScore(0);
  setMoving(sf::Keyboard::Scancode::D);
  setLastMoving();
  setTimeGap(baseTime);
  setLose(false);
  setPaused(false);
  getWindow().reset(score);
}

void Game::run() { Events::handleEvents(*this); }

void Game::move() {
  switch (getMoving()) {
  case sf::Keyboard::Scancode::W:
    getWindow().moveSnake(*this, sf::Vector2f(0, -1));
    break;
  case sf::Keyboard::Scancode::S:
    getWindow().moveSnake(*this, sf::Vector2f(0, 1));
    break;
  case sf::Keyboard::Scancode::A:
    getWindow().moveSnake(*this, sf::Vector2f(-1, 0));
    break;
  case sf::Keyboard::Scancode::D:
    getWindow().moveSnake(*this, sf::Vector2f(1, 0));
    break;
  default:
    break;
  }
  setLastMoving();
}

void Game::lost() {
  setLose(true);
  getWindow().lose(getScore());
}

void Game::pause() {
  setPaused(true);
  getWindow().pause();
}

void Game::resume() { setPaused(false); }

void Game::close() { window->close(); }

bool Game::isOpen() const { return getWindow().isOpen(); }

void Game::drawShapes() { getWindow().drawShapes(); }
