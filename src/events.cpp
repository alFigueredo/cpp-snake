#include "events.hpp"
#include "game.hpp"

bool Events::checkMovingKeys(const sf::Keyboard::Scancode &lastKey,
                             const sf::Keyboard::Scancode &currentKey) {
  switch (currentKey) {
  case sf::Keyboard::Scancode::A:
  case sf::Keyboard::Scancode::D:
    return lastKey != sf::Keyboard::Scancode::A &&
           lastKey != sf::Keyboard::Scancode::D;
  case sf::Keyboard::Scancode::W:
  case sf::Keyboard::Scancode::S:
    return lastKey != sf::Keyboard::Scancode::W &&
           lastKey != sf::Keyboard::Scancode::S;
  default:
    return false;
  }
}

void Events::handleEvents(Game &game) {
  const auto eventClosed = [&game](const sf::Event::Closed &) { game.close(); };
  const auto eventFocusLost = [&game](const sf::Event::FocusLost &) {
    game.pause();
  };
  const auto eventFocusGained = [&game](const sf::Event::FocusGained &) {
    game.resume();
  };
  const auto eventKeyPressed =
      [&game](const sf::Event::KeyPressed &keyPressed) {
        const sf::Keyboard::Scancode lastKey = game.getLastMoving();
        const sf::Keyboard::Scancode currentKey = keyPressed.scancode;
        switch (currentKey) {
        case sf::Keyboard::Scancode::A:
        case sf::Keyboard::Scancode::D:
        case sf::Keyboard::Scancode::W:
        case sf::Keyboard::Scancode::S:
          if (checkMovingKeys(lastKey, currentKey))
            game.setMoving(currentKey);
          break;
        case sf::Keyboard::Scancode::R:
          game.reset();
          break;
        case sf::Keyboard::Scancode::P:
          if (game.isPaused())
            game.resume();
          else
            game.pause();
          break;
        default:
          break;
        }
      };
  game.getWindow().handleEvents(eventClosed, eventFocusLost, eventFocusGained,
                                eventKeyPressed);
}
