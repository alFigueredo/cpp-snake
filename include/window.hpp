#pragma once

#include "food.hpp"
#include "random_manager.hpp"
#include "snake.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

class Game;

class Window {
private:
  const std::string title;
  const unsigned widthP = 512;
  const unsigned heightP = 384;
  const unsigned size = 16;
  sf::RenderWindow window;
  const std::unique_ptr<Snake> snake;
  const std::unique_ptr<Food> food;
  sf::Font font;
  std::unique_ptr<sf::Text> text;
  std::unique_ptr<RandomManager> randomManager;

public:
  Window(const std::string &title_);

  int getSize() const;
  float getSizef() const;
  int getWidthP() const;
  int getHeightP() const;
  unsigned getWidth() const;
  unsigned getHeight() const;
  Snake &getSnake() const;
  Food &getFood() const;
  sf::RenderWindow &getWindow();

  void setTextString(const std::string &text);
  void drawShape(const sf::Drawable &shape);
  void reset(const unsigned &score);
  void adaptVector2(sf::Vector2i &vector) const;
  void moveSnake(Game &game, sf::Vector2i &&vector);
  void lose(const unsigned &score);
  void pause();
  void close();
  void drawShapes();
  bool isOpen() const;
  sf::RectangleShape new_shape(const sf::Vector2i &pos,
                               const sf::Color &color = sf::Color::Green) const;
};
