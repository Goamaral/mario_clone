#include "Color.hpp"

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  red = r;
  green = g;
  blue = b;
  alpha = a;
}

Color::Color(Uint32 rgba) {
  red = (rgba >> 24) & 0xFF;
  green = (rgba >> 16) & 0xFF;
  blue = (rgba >> 8) & 0xFF;
  alpha = rgba & 0xFF;
}

Color::Color(std::string color_name) {
  if (color_name == "red") { red = 0xFF; }
  else if (color_name == "green") { green = 0XFF; }
  else if (color_name == "blue") { blue = 0XFF; }
  else if (color_name == "yellow") { red = 0XFF; green = 0XFF; }
  else if (color_name == "magenta") { red = 0XFF; blue = 0XFF; }
  else if (color_name == "cyan") { green = 0XFF; blue = 0XFF; }
  else if (color_name == "white") { red = 0XFF; green = 0XFF; blue = 0xFF; }
}