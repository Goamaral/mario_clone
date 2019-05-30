
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.hpp"
#endif

class Window {
  public:
    Window();
    Window(std::string, int, int);
    ~Window();

    void render_surface(SDL_Surface*);
    void render_texture(SDL_Texture*);
    void set_viewport(SDL_Rect*);
    void render_viewports();

    SDL_Window* p = NULL;
    bool loaded = false;

    SDL_Renderer* renderer_p = NULL;
    SDL_Surface* surface_p = NULL;
};