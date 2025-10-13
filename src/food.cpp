#include "food.hpp"
#include "window.hpp"

Food::Food(const float &size) : food(sf::RectangleShape({size, size})) {
  food.setFillColor(sf::Color::Blue);
}

void Food::reset(const sf::Vector2i &position) {
  food.setPosition(sf::Vector2f(position));
}

sf::Vector2i Food::getPosition() const {
  return sf::Vector2i(food.getPosition());
}

void Food::draw(Window &window) const { window.drawShape(food); }
