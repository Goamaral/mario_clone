#ifndef SURFACE_H
#define SURFACE_H

#include <memory>
#include <string>
#include <exception>

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_log.h>

class Surface {
  public:
    SDL_Surface* sdl_p;

    Surface(SDL_Surface*);
    ~Surface();

    static Surface* load_from_bmp(std::string);

  private:
};

#endif