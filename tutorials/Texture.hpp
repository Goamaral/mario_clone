#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdio>
#include <string>

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.hpp"
#endif

enum class TextureColorMode {
  NONE,
  COLOR_KEYING,
  COLOR_MODULATION
};

struct texture_t {
  SDL_Texture* p = NULL;
  int width = 0;
  int height = 0;
  bool loaded = false;

  texture_t(SDL_Texture* = NULL, int = 0, int = 0);
  ~texture_t();
};

texture_t* texture_load_from_file(std::string, SDL_Renderer*, TextureColorMode = TextureColorMode::NONE, Uint8 = 0xFF, Uint8 = 0xFF, Uint8 = 0xFF);
void texture_free(SDL_Texture*);