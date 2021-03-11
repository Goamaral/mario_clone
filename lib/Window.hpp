#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_image.h>

#include "Texture.hpp"
#include "Surface.hpp"
#include "Color.hpp"

class Window {
  public:
    Window();
    ~Window();

    // STATIC METHODS

    // INSTANCE METHODS
    // GENERAL
    void init(std::string, int, int);

    // RENDERER
    void renderer_render();
    void renderer_set_draw_color(Color);
    void renderer_set_viewport(SDL_Rect*);
    void renderer_clear();
    void renderer_reset();

    // SURFACES
    void render_surface(Surface*, bool = false);

    // TEXTURES
    void render_texture(Texture*);
    void render_rectangle(int, int, int, int, Color);
    void render_rectangle_outline(int, int, int, int, Color);
    void render_line(int, int, int, int, Color);
    void render_point(int, int, Color);

    // GETTERS
    SDL_PixelFormat* surface_pixel_format();
    SDL_Renderer* sdl_renderer_p();

  private:
    SDL_Window* $sdl_p;
    SDL_Renderer* $sdl_renderer_p;
    SDL_Surface* $sdl_surface_p;
    std::string $title;
    int $width;
    int $height;
};

#endif