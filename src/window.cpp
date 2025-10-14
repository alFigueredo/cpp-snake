#include "window.hpp"
#include "font.hpp"
#include "game.hpp"

Window::Window(const std::string &title)
    : window(sf::RenderWindow(sf::VideoMode({widthP, heightP}), title)),
      font(Font::getFont("./assets/fonts/DejaVuSans.ttf")),
      randomManager(std::make_unique<RandomManager>(getWidth(), getHeight())) {
  text = std::make_unique<sf::Text>(font, "", 24);
  text->setFillColor(sf::Color::White);
  text->setPosition(sf::Vector2f(widthP - 160, 0));
}

int Window::getSize() const { return size; }
float Window::getSizef() const { return size; }
int Window::getWidthP() const { return widthP; }
int Window::getHeightP() const { return heightP; }
unsigned Window::getWidth() const { return getWidthP() / size; }
unsigned Window::getHeight() const { return getHeightP() / size; }
RandomManager &Window::getRandomManager() const { return *randomManager; }
sf::RenderWindow &Window::getWindow() { return window; }

void Window::setTextString(const std::string &string) {
  text->setString(string);
}

void Window::drawShape(const sf::Drawable &shape) { getWindow().draw(shape); }

void Window::reset(const unsigned &score) {
  setTextString("Score: " + std::to_string(score));
}

void Window::adaptMove(sf::Vector2i &vector,
                       const sf::Vector2i &snakePos) const {
  const sf::Vector2i newVector(vector * getSize() + snakePos);
  vector.x = newVector.x < 0              ? getWidthP() - getSize()
             : newVector.x >= getWidthP() ? 0
                                          : newVector.x;
  vector.y = newVector.y < 0               ? getHeightP() - getSize()
             : newVector.y >= getHeightP() ? 0
                                           : newVector.y;
}

void Window::lose(const unsigned &score) {
  setTextString("Final: " + std::to_string(score));
}

void Window::pause() { setTextString("Paused"); }

void Window::close() { window.close(); }

bool Window::isOpen() const { return window.isOpen(); }

sf::Vector2i Window::getRandomVector2() {
  return getRandomManager().getVector2() * getSize();
}

void Window::displayShapes(Game &game) {
  getWindow().clear();
  game.drawShapes();
  drawShape(*text);
  getWindow().display();
}

sf::RectangleShape Window::new_shape(const sf::Vector2i &position,
                                     const sf::Color &color) const {
  sf::RectangleShape shape(sf::Vector2f(getSize(), getSize()));
  shape.setFillColor(color);
  shape.setPosition(sf::Vector2f(position));
  return shape;
}
