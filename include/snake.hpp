#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>

class Window;

class Snake {
private:
  std::list<sf::RectangleShape> body;

public:
  Snake();
  void reset(const Window &window);
  void fillColor(const sf::Color &color);
  bool collision(const sf::Vector2i &position);
  bool self_collision(sf::Vector2i move);
  void move(const Window &window, const sf::Vector2i &move);
  void moveTail();
  sf::Vector2i getPosition();
  void draw(Window &window);
};
