#include "snake.hpp"
#include "window.hpp"
#include <algorithm>

Snake::Snake() {}

void Snake::fillColor(const sf::Color &color) {
  std::for_each(body.begin(), body.end(), [&color](sf::RectangleShape &item) {
    return item.setFillColor(color);
  });
}

void Snake::reset(const Window &window) {
  body.clear();
  body.push_front(window.new_shape(sf::Vector2f(2, 0), sf::Color::Yellow));
  for (unsigned i = 0; i < 2; ++i)
    body.push_front(window.new_shape(sf::Vector2f(i, 0)));
}

bool Snake::collision(const sf::Vector2f &position) {
  return std::any_of(body.begin(), body.end(),
                     [&position](sf::RectangleShape &item) {
                       return position == item.getPosition();
                     });
}

bool Snake::self_collision(sf::Vector2f move) {
  std::any_of(body.begin(), body.end() - 1, [&move](sf::RectangleShape &item) {
    return move == item.getPosition();
  });
  return true;
}

void Snake::move(const Window &window, const sf::Vector2f &move) {
  if (self_collision(move))
    return;
  body.push_front(window.new_shape(move, sf::Color::Yellow));
}

sf::Vector2f Snake::getPosition() { return body.begin()->getPosition(); }
