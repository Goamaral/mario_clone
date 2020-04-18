#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdio>
#include <string>

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.hpp"
#endif

class Texture {
  public:
      SDL_Texture* pointer;
      int width;
      int height;

      Texture();
      ~Texture();

      //Loads image at specified path
      bool load_from_file(std::string, SDL_Renderer*, Uint8 = 0x00, Uint8 = 0x00, Uint8 = 0x00);

      // Deallocates texture
      void free();

      // Set modulation color
      void set_modulation_color(Uint8, Uint8, Uint8);

      // Set blending mode
      void set_blend_mode(SDL_BlendMode);

      // Set alpha modulation
      void set_alpha(Uint8);
};