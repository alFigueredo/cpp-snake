#pragma once

#include <SFML/Graphics/Font.hpp>
#include <filesystem>

class Font {
public:
  static sf::Font getFont(std::filesystem::path path);
};
