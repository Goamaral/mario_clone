#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.hpp"
#endif


class Window {
  public:
    Window(std::string, int, int);
    ~Window();

    SDL_Window* pointer = NULL;
    SDL_Renderer* renderer_p = NULL;
    SDL_Surface* surface_p = NULL;
    bool loaded = false;

    SDL_Renderer* loadRenderer();
    SDL_Surface* loadSurface();
    void render_surface(SDL_Surface*);
};