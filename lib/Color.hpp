#ifndef COLOR_H
#define COLOR_H

#include <string>

#include <SDL2/SDL.h>

class Color {
  public:
    Color(Uint8, Uint8, Uint8, Uint8);
    Color(Uint32);
    Color(std::string);

    Uint8 red = 0;
    Uint8 green = 0;
    Uint8 blue = 0;
    Uint8 alpha = 0XFF;
};

#endif