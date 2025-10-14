#pragma once

#include "events.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "window.hpp"
#include <SFML/Window/Keyboard.hpp>

class Game {
private:
  const std::string title;
  unsigned int score;
  sf::Keyboard::Scancode moving;
  sf::Keyboard::Scancode lastMoving;
  const unsigned int baseTime = 1024;
  const unsigned int baseGap = 16;
  const unsigned int baseLimit = 48;
  unsigned int timeGap;
  bool lose;
  bool paused;
  const std::unique_ptr<Window> window;
  const std::unique_ptr<Snake> snake;
  const std::unique_ptr<Food> food;
  Game(const std::string &title_);

public:
  Game(const Game &) = delete;
  void operator=(const Game &) = delete;

  static Game &initInstance(const std::string &title);

  unsigned getScore() const;
  sf::Keyboard::Scancode getMoving() const;
  sf::Keyboard::Scancode getLastMoving() const;
  unsigned getBaseTime() const;
  unsigned getBaseLimit() const;
  unsigned getBaseGap() const;
  unsigned getTimeGap() const;
  bool isLose() const;
  bool isPaused() const;
  bool isRunning() const;
  Window &getWindow() const;
  Snake &getSnake() const;
  Food &getFood() const;

  void setScore(const unsigned &score);
  void setMoving(const sf::Keyboard::Scancode &moving);
  void setLastMoving();
  void setTimeGap(const unsigned &timeGap);
  void setLose(const bool &lose);
  void setPaused(const bool &paused);
  void reduceTimeGap();

  void reset();
  void run();
  void moveSnake(sf::Vector2i &&vector);
  void move();
  void lost();
  void pause();
  void resume();
  void close();
  bool isOpen() const;
  void displayShapes();
  void drawShapes();
};
