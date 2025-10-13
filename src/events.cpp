#include "events.hpp"
#include "game.hpp"
#include <iostream>

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
        const sf::Keyboard::Scancode actualKey = keyPressed.scancode;
        if (((actualKey == sf::Keyboard::Scancode::A ||
              actualKey == sf::Keyboard::Scancode::D) &&
             (lastKey != sf::Keyboard::Scancode::A &&
              lastKey != sf::Keyboard::Scancode::D)) ||
            ((actualKey == sf::Keyboard::Scancode::W ||
              actualKey == sf::Keyboard::Scancode::S) &&
             (lastKey != sf::Keyboard::Scancode::W &&
              lastKey != sf::Keyboard::Scancode::S)))
          game.setMoving(keyPressed.scancode);
        else if (actualKey == sf::Keyboard::Scancode::R)
          game.reset();
        else if (actualKey == sf::Keyboard::Scancode::P) {
          if (game.isPaused())
            game.resume();
          else
            game.pause();
        }
      };
  while (game.isOpen()) {
    game.getWindow().getWindow().handleEvents(
        eventClosed, eventFocusLost, eventFocusGained, eventKeyPressed);
    if (game.isRunning())
      game.move();
    game.drawShapes();
    sf::sleep(
        sf::milliseconds(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X)
                             ? game.getBaseLimit()
                             : game.getTimeGap()));
  }
}
