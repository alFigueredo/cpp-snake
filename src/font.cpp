#include "font.hpp"
#include <iostream>

sf::Font Font::getFont(std::filesystem::path path) {
  sf::Font font;
  if (!font.openFromFile(path)) {
    std::cerr << "Error: cannot load font!" << std::endl;
    exit(1);
  }
  return font;
}
