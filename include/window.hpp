#pragma once

#include "random_manager.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

class Game;

class Window {
private:
  const unsigned widthP = 512;
  const unsigned heightP = 384;
  const unsigned size = 16;
  sf::RenderWindow window;
  sf::Font font;
  std::unique_ptr<sf::Text> text;
  std::unique_ptr<RandomManager> randomManager;

public:
  Window(const std::string &title);

  int getSize() const;
  float getSizef() const;
  int getWidthP() const;
  int getHeightP() const;
  unsigned getWidth() const;
  unsigned getHeight() const;
  RandomManager &getRandomManager() const;
  sf::RenderWindow &getWindow();

  void setTextString(const std::string &text);
  void drawShape(const sf::Drawable &shape);
  void reset(const unsigned &score);
  void adaptMove(sf::Vector2i &vector, const sf::Vector2i &snakePos) const;
  void lose(const unsigned &score);
  void pause();
  void close();
  bool isOpen() const;
  sf::Vector2i getRandomVector2();
  void drawShapes(const Game &game);
  sf::RectangleShape new_shape(const sf::Vector2i &pos,
                               const sf::Color &color = sf::Color::Green) const;
};
