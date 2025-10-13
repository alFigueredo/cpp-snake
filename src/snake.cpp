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
  move(window, sf::Vector2i(0, 0));
  move(window, sf::Vector2i(1 * window.getSize(), 0));
  move(window, sf::Vector2i(2 * window.getSize(), 0));
}

bool Snake::collision(const sf::Vector2i &position) {
  return std::any_of(body.begin(), body.end(),
                     [&position](const sf::RectangleShape &item) {
                       return position == sf::Vector2i(item.getPosition());
                     });
}

bool Snake::self_collision(sf::Vector2i move) {
  return std::any_of(body.begin(), --body.end(),
                     [&move](const sf::RectangleShape &item) {
                       return move == sf::Vector2i(item.getPosition());
                     });
}

void Snake::move(const Window &window, const sf::Vector2i &move) {
  if (!body.empty())
    body.front().setFillColor(sf::Color::Green);
  body.push_front(window.new_shape(move, sf::Color::Yellow));
}

void Snake::moveTail() { body.pop_back(); }

sf::Vector2i Snake::getPosition() {
  return sf::Vector2i(body.front().getPosition());
}

void Snake::draw(Window &window) {
  std::for_each(body.begin(), body.end(), [&window](sf::RectangleShape &shape) {
    window.drawShape(shape);
  });
}
