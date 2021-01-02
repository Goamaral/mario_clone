#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_image.h>

#include "Texture.hpp"
#include "Surface.hpp"

class Window {
  public:
    Window();
    ~Window();

    // STATIC METHODS

    // INSTANCE METHODS
    // GENERAL
    void init(std::string, int, int);
    void renderer_render();
    void renderer_clear();

    // SURFACES
    void render_surface(Surface*, bool = false);

    // TEXTURES
    std::shared_ptr<Texture> load_texture_from_png(std::string, std::string);
    void render_texture(std::string);

    // GETTERS
    SDL_PixelFormat* surface_pixel_format();

    // LEGACY
    // void renderer_apply_texture(Texture*, SDL_Rect, SDL_Rect);

  private:
    SDL_Window* $sdl_p;
    SDL_Renderer* $sdl_renderer_p;
    SDL_Surface* $sdl_surface_p;
    std::string $title;
    int $width;
    int $height;
    std::unordered_map<std::string, std::shared_ptr<Texture>> $textures;
};

#endif