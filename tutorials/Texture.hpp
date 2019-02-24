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
    Texture();
    ~Texture();

    int width = 0;
    int height = 0;

    static SDL_Texture* load(std::string, SDL_Renderer*);
    static void free(SDL_Texture*);
    static SDL_Texture* loadFromFile(std::string path, SDL_Renderer* renderer_p);
};