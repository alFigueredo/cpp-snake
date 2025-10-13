#include "window.hpp"
#include "font.hpp"
#include "game.hpp"

Window::Window(const std::string &title_)
    : title(title_),
      window(sf::RenderWindow(sf::VideoMode({widthP, heightP}), title_)),
      snake(std::make_unique<Snake>()),
      food(std::make_unique<Food>(getSizef())),
      font(Font::getFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")),
      randomManager(std::make_unique<RandomManager>(getWidth(), getHeight())) {
  text = std::make_unique<sf::Text>(font, "", 24);
  text->setFillColor(sf::Color::White);
  text->setPosition(sf::Vector2f(widthP - 160, 0));
}

unsigned Window::getSize() const { return size; }
float Window::getSizef() const { return size; }
unsigned Window::getWidthP() const { return widthP; }
unsigned Window::getHeightP() const { return heightP; }
unsigned Window::getWidth() const { return getWidthP() / size; }
unsigned Window::getHeight() const { return getHeightP() / size; }
Snake &Window::getSnake() const { return *snake; }
Food &Window::getFood() const { return *food; }
sf::RenderWindow &Window::getWindow() { return window; }

void Window::setTextString(const std::string &string) {
  text->setString(string);
}

void Window::reset(const unsigned &score) {

  getSnake().reset(*this);
  do
    getFood().reset(randomManager->getVector2f(getSize()));
  while (snake->collision(food->getPosition()));
  setTextString("Score: " + std::to_string(score));
}

sf::Vector2f Window::getVector2f(const sf::Vector2f &vector) const {
  const sf::Vector2f newVector(vector * getSizef() + getSnake().getPosition());
  const float x = newVector.x < 0              ? getWidthP() - getSize()
                  : newVector.x >= getWidthP() ? 0
                                               : newVector.x;
  const float y = newVector.y < 0               ? getHeightP() - getSize()
                  : newVector.y >= getHeightP() ? 0
                                                : newVector.y;
  return sf::Vector2f(x, y);
}

void Window::moveSnake(Game &game, const sf::Vector2f &vector) {
  const sf::Vector2f newVector = getVector2f(vector);
  if (getSnake().self_collision(newVector)) {
    game.lost();
    return;
  }
  getSnake().move(*this, newVector);
  if (getSnake().getPosition() == getFood().getPosition()) {
    game.setScore(game.getScore() + 10);
    game.reduceTimeGap();
    do
      getFood().reset(randomManager->getVector2f(getSize()));
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
  getWindow().draw(*text);
  getWindow().display();
}

sf::RectangleShape Window::new_shape(const sf::Vector2f &pos,
                                     const sf::Color &color) const {
  sf::RectangleShape shape(sf::Vector2f(getSizef(), getSizef()));
  shape.setFillColor(color);
  shape.setPosition(pos);
  return shape;
}
