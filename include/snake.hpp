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
  bool collision(const sf::Vector2f &position);
  bool self_collision(sf::Vector2f move);
  void move(const Window &window, const sf::Vector2f &move);
  void moveTail();
  sf::Vector2f getPosition();
  void draw(Window &window);
};
