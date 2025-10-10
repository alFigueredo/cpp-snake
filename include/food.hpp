#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Food {
private:
  sf::RectangleShape food;

public:
  Food(const float &size);

  void reset(const sf::Vector2f &position);

  sf::Vector2f getPosition() const;
};
