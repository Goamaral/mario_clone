#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdio>
#include <string>

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.hpp"
#endif

struct texture_t {
  SDL_Texture* p = NULL;
  int width = 0;
  int height = 0;
  bool loaded = false;

  texture_t(SDL_Texture* = NULL, int = 0, int = 0);
  ~texture_t();
};

texture_t* texture_load_from_file(std::string, SDL_Renderer*, bool = false, int = 255, int = 255, int = 255);
void texture_free(SDL_Texture*);