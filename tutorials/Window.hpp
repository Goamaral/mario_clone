
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.hpp"
#endif

// Screen dimension constants
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "SDL Tutorial"

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
void window_reset_renderer();
void window_render_renderer();
void window_set_renderer_color(Uint8, Uint8, Uint8, Uint8);
void window_add_geo_rect(SDL_Rect*);
void window_add_geo_line(int, int, int, int);
void window_add_geo_point(int, int);