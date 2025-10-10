#pragma once

#include "events.hpp"
#include "window.hpp"
#include <SFML/Window/Keyboard.hpp>

class Game {
private:
  const std::string title;
  unsigned int score;
  sf::Keyboard::Scancode moving;
  const unsigned int baseTime = 1024;
  const unsigned int baseGap = 16;
  const unsigned int baseLimit = 48;
  unsigned int timeGap;
  bool lose;
  bool paused;
  const std::unique_ptr<Window> window;
  Game(const std::string &title_);

public:
  Game(const Game &) = delete;
  void operator=(const Game &) = delete;

  static Game &initInstance(const std::string &title);

  unsigned getScore() const;
  sf::Keyboard::Scancode getMoving() const;
  unsigned getBaseTime() const;
  bool getLose() const;
  bool getPaused() const;
  Window &getWindow() const;

  void setScore(const unsigned &score);
  void setMoving(const sf::Keyboard::Scancode &moving);
  void setTimeGap(const unsigned &timeGap);
  void setLose(const bool &lose);
  void setPaused(const bool &paused);

  void reset();
  void run();
  void move();
  void lost();
  void pause();
  void close();
  bool isOpen() const;
};
