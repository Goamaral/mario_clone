#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <memory>
#include <functional>

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
    std::shared_ptr<Window> create_window(std::string, int, int);
    void delay(Uint32);
    void event_loop(std::function<bool(SDL_Event)>);

  private:
    bool $sdl_inited;
    bool $sdl_img_inited;
    std::vector< std::shared_ptr<Window> > $windows;
};

#endif