#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"

class System {
  public:
    System();
    ~System();

    // STATIC METHODS

    // INSTANCE METHODS
    // GENERAL
    void init(Uint32);
    void init_png_img();
    void delay(Uint32);

    // WINDOWS
    std::shared_ptr<Window> create_window(std::string, std::string, int, int);

    // SURFACES
    std::shared_ptr<Surface> load_surface_from_bmp(std::string, std::string, std::string);
    std::shared_ptr<Surface> load_surface_from_png(std::string, std::string, std::string);
    void render_surface(std::string, std::string, bool = false);

    // TEXTURES
    std::shared_ptr<Texture> load_texture_from_png(std::string, std::string, std::string);
    void render_texture(std::string, std::string);

    // GETTERS
    std::shared_ptr<Window> window(std::string);

    private:
      bool $sdl_inited;
      bool $sdl_img_inited;
      bool $sdl_png_img_inited;
      std::unordered_map<std::string, std::shared_ptr<Window>> $windows;
      std::unordered_map<std::string, std::shared_ptr<Surface>> $surfaces;
      std::unordered_map<std::string, std::shared_ptr<Texture>> $textures;
    };

#endif