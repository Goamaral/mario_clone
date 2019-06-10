
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.hpp"
#endif

struct window_t {
  SDL_Window* p = NULL;
  SDL_Renderer* renderer_p = NULL;
  SDL_Surface* surface_p = NULL;
};

extern window_t* global_window_p;

bool window_init(std::string, int, int);
void window_destroy();
void window_render_surface(SDL_Surface*);
void window_render_texture(SDL_Texture*);
void window_set_viewport(SDL_Rect*);
void window_render_viewports();