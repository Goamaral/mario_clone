#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdio>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>

#include "Surface.hpp"

class Texture {
  public:
      Texture(SDL_Texture*, int, int);
      ~Texture();

      // STATIC METHODS
      static Texture* load_from_png(std::string, SDL_Renderer*);

      // INSTANCE METHODS

      // GETTERS
      SDL_Texture* sdl_p();

      // LEGACY
      // // Loads image at specified path
      // bool load_from_file(std::string, SDL_Renderer*, Uint8 = 0x00, Uint8 = 0x00, Uint8 = 0x00);

      // // Deallocates texture
      // void free();

      // // Set modulation color
      // void set_modulation_color(Uint8, Uint8, Uint8);

      // // Set blending mode
      // void set_blend_mode(SDL_BlendMode);

      // // Set alpha modulation
      // void set_alpha(Uint8);

  private:
    SDL_Texture* $sdl_p;
    int $width;
    int $height;
};

#endif