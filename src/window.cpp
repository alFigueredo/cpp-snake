#include "window.hpp"
#include "font.hpp"
#include "game.hpp"

Window::Window(const std::string &title_)
    : title(title_),
      window(sf::RenderWindow(sf::VideoMode({widthP, heightP}), title_)),
      snake(std::make_unique<Snake>()),
      food(std::make_unique<Food>(getSizef())),
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
Snake &Window::getSnake() const { return *snake; }
Food &Window::getFood() const { return *food; }
sf::RenderWindow &Window::getWindow() { return window; }

void Window::setTextString(const std::string &string) {
  text->setString(string);
}

void Window::drawShape(const sf::Drawable &shape) { getWindow().draw(shape); }

void Window::reset(const unsigned &score) {
  getSnake().reset(*this);
  do
    getFood().reset(randomManager->getVector2() * getSize());
  while (getSnake().collision(getFood().getPosition()));
  setTextString("Score: " + std::to_string(score));
}

void Window::adaptVector2(sf::Vector2i &vector) const {
  const sf::Vector2i newVector(vector * getSize() + getSnake().getPosition());
  vector.x = newVector.x < 0              ? getWidthP() - getSize()
             : newVector.x >= getWidthP() ? 0
                                          : newVector.x;
  vector.y = newVector.y < 0               ? getHeightP() - getSize()
             : newVector.y >= getHeightP() ? 0
                                           : newVector.y;
}

void Window::moveSnake(Game &game, sf::Vector2i &&vector) {
  adaptVector2(vector);
  if (getSnake().self_collision(vector)) {
    game.lost();
    return;
  }
  getSnake().move(*this, vector);
  if (getSnake().getPosition() == getFood().getPosition()) {
    game.setScore(game.getScore() + 10);
    game.reduceTimeGap();
    do
      getFood().reset(randomManager->getVector2() * getSize());
    while (getSnake().collision(getFood().getPosition()));
  } else
    getSnake().moveTail();
  setTextString("Score: " + std::to_string(game.getScore()));
};

void Window::lose(const unsigned &score) {
  getSnake().fillColor(sf::Color::Red);
  setTextString("Final: " + std::to_string(score));
}

void Window::pause() { setTextString("Paused"); }

void Window::close() { window.close(); }

bool Window::isOpen() const { return window.isOpen(); }

void Window::drawShapes() {
  getWindow().clear();
  getSnake().draw(*this);
  getFood().draw(*this);
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
