#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_image.h>

#include "NewWindow.hpp"

class System {
  public:
    System();
    ~System();

    void init(Uint32);
    void init_img_support(int);
    std::shared_ptr<Window> create_window(std::string, std::string, int, int);
    void delay(Uint32);
    std::shared_ptr<Surface> load_surface_from_bmp(std::string, std::string);
    void render_surface(std::string, std::string);

  private:
    bool $sdl_inited;
    bool $sdl_img_inited;
    std::unordered_map< std::string, std::shared_ptr<Window> > $windows;
    std::unordered_map< std::string, std::shared_ptr<Surface> > $surfaces;
};

#endif