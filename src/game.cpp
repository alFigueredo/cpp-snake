#include "game.hpp"

Game::Game(const std::string &title_)
    : title(title_), window(std::make_unique<Window>(title_)),
      snake(std::make_unique<Snake>()),
      food(std::make_unique<Food>(getWindow().getSizef())) {
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
Snake &Game::getSnake() const { return *snake; }
Food &Game::getFood() const { return *food; }

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
  getSnake().reset(getWindow());
  do
    getFood().reset(getWindow().getRandomVector2());
  while (getSnake().collision(getFood().getPosition()));
  getWindow().reset(score);
}

void Game::run() {
  while (isOpen()) {
    Events::handleEvents(*this);
    if (isRunning())
      move();
    drawShapes();
    sf::sleep(sf::milliseconds(
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X) ? getBaseLimit()
                                                              : getTimeGap()));
  }
}

void Game::moveSnake(sf::Vector2i &&vector) {
  getWindow().adaptMove(vector, getSnake().getPosition());
  if (getSnake().self_collision(vector)) {
    lost();
    return;
  }
  getSnake().move(getWindow(), vector);
  if (getSnake().getPosition() == getFood().getPosition()) {
    setScore(getScore() + 10);
    reduceTimeGap();
    do
      getFood().reset(getWindow().getRandomVector2());
    while (getSnake().collision(getFood().getPosition()));
  } else
    getSnake().moveTail();
  getWindow().setTextString("Score: " + std::to_string(getScore()));
};

void Game::move() {
  switch (getMoving()) {
  case sf::Keyboard::Scancode::W:
    moveSnake(sf::Vector2i(0, -1));
    break;
  case sf::Keyboard::Scancode::S:
    moveSnake(sf::Vector2i(0, 1));
    break;
  case sf::Keyboard::Scancode::A:
    moveSnake(sf::Vector2i(-1, 0));
    break;
  case sf::Keyboard::Scancode::D:
    moveSnake(sf::Vector2i(1, 0));
    break;
  default:
    break;
  }
  setLastMoving();
}

void Game::lost() {
  setLose(true);
  getSnake().fillColor(sf::Color::Red);
  getWindow().lose(getScore());
}

void Game::pause() {
  setPaused(true);
  getWindow().pause();
}

void Game::resume() { setPaused(false); }

void Game::close() { getWindow().close(); }

bool Game::isOpen() const { return getWindow().isOpen(); }

void Game::drawShapes() { getWindow().drawShapes(*this); }
