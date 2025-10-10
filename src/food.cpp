#include "food.hpp"

Food::Food(const float &size) : food(sf::RectangleShape({size, size})) {
  food.setFillColor(sf::Color::Blue);
}

void Food::reset(const sf::Vector2f &position) { food.setPosition(position); }

sf::Vector2f Food::getPosition() const { return food.getPosition(); }
