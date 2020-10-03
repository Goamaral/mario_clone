#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_image.h>

#include "Texture.hpp"
#include "NewSurface.hpp"

class Window {
  public:
    Window();
    ~Window();

    void init(std::string, int, int);
    void render_surface(Surface*);
    void renderer_apply_texture(Texture*, SDL_Rect, SDL_Rect);
    void renderer_render();
    void renderer_clear();

  private:
    SDL_Window* $sdl_p;
    SDL_Renderer* $sdl_renderer_p;
    SDL_Surface* $sdl_surface_p;
    std::string $title;
    int $width;
    int $height;
};

#endif