#include "snake.hpp"
#include "window.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <algorithm>

Snake::Snake() {}

void Snake::fillColor(const sf::Color &color) {
  std::for_each(body.begin(), body.end(), [&color](sf::RectangleShape &item) {
    return item.setFillColor(color);
  });
}

void Snake::reset(const Window &window) {
  body.clear();
  body.push_front(window.new_shape(sf::Vector2f(0, 0)));
  body.push_front(window.new_shape(sf::Vector2f(1 * window.getSizef(), 0)));
  body.push_front(window.new_shape(sf::Vector2f(2 * window.getSizef(), 0),
                                   sf::Color::Yellow));
}

bool Snake::collision(const sf::Vector2f &position) {
  return std::any_of(body.begin(), body.end(),
                     [&position](const sf::RectangleShape &item) {
                       return position == item.getPosition();
                     });
}

bool Snake::self_collision(sf::Vector2f move) {
  return std::any_of(body.begin(), --body.end(),
                     [&move](const sf::RectangleShape &item) {
                       return move == item.getPosition();
                     });
}

void Snake::move(const Window &window, const sf::Vector2f &move) {
  body.front().setFillColor(sf::Color::Green);
  body.push_front(window.new_shape(move, sf::Color::Yellow));
}

void Snake::moveTail() { body.pop_back(); }

sf::Vector2f Snake::getPosition() { return body.front().getPosition(); }

void Snake::draw(Window &window) {
  std::for_each(body.begin(), body.end(), [&window](sf::RectangleShape &shape) {
    window.getWindow().draw(shape);
  });
}
