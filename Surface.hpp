#ifndef SURFACE_H
#define SURFACE_H

#include <memory>
#include <string>
#include <exception>

#include <SDL2/SDL.h>
#include <SDL2/SDL_assert.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_image.h>

class Surface {
  public:
    SDL_Surface* $sdl_p;

    Surface(SDL_Surface*);
    ~Surface();

    // STATIC METHODS
    static SDL_Surface* optimize_sdl_surface(SDL_Surface*, SDL_PixelFormat*);
    static Surface* load_from_bmp(std::string, SDL_PixelFormat* = NULL);
    static Surface* load_from_png(std::string, SDL_PixelFormat* = NULL);
    static void copy_scaled(SDL_Surface*, SDL_Surface*);
    static void copy(SDL_Surface*, SDL_Surface*);

    // INSTANCE METHODS

    // GETTERS
    SDL_Surface* sdl_p();
    int width();
    int height();

  private:
};

#endif