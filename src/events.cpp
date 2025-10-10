#include "events.hpp"
#include "game.hpp"

void Events::handleEvents(Game &game) {
  const auto eventClosed = [&game](const sf::Event::Closed &) { game.close(); };
  const auto eventFocusLost = [&game](const sf::Event::FocusLost &) {
    game.setPaused(false);
  };
  const auto eventFocusGained = [&game](const sf::Event::FocusGained &) {
    game.setPaused(true);
  };
  const auto eventKeyPressed =
      [&game](const sf::Event::KeyPressed &keyPressed) {
        const sf::Keyboard::Scancode lastKey = game.getMoving();
        const sf::Keyboard::Scancode actualKey = keyPressed.scancode;
        if (((lastKey == sf::Keyboard::Scancode::A ||
              lastKey == sf::Keyboard::Scancode::D) &&
             (actualKey == sf::Keyboard::Scancode::W ||
              actualKey == sf::Keyboard::Scancode::S)) ||
            ((lastKey == sf::Keyboard::Scancode::W ||
              lastKey == sf::Keyboard::Scancode::S) &&
             (actualKey == sf::Keyboard::Scancode::A ||
              actualKey == sf::Keyboard::Scancode::D)))
          return;
        if (actualKey == sf::Keyboard::Scancode::R) {
          game.reset();
          return;
        }
        if (actualKey == sf::Keyboard::Scancode::P) {
          game.setPaused(!game.getPaused());
        }
        game.setMoving(keyPressed.scancode);
      };
  while (game.isOpen()) {
    game.getWindow().getWindow().handleEvents(
        eventClosed, eventFocusLost, eventFocusGained, eventKeyPressed);
  }
}
