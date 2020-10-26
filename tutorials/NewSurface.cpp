#include "NewSurface.hpp"

Surface::Surface(SDL_Surface* sdl_surface_p) {
  sdl_p = sdl_surface_p;
}

Surface::~Surface() {
  if (sdl_p) SDL_FreeSurface(sdl_p);
}

/* STATIC METHODS */
Surface* Surface::load_from_bmp(std::string image_location) {
  SDL_Surface* sdl_surface_p = SDL_LoadBMP(image_location.c_str());

  if (sdl_surface_p == NULL) {
    const char* error_message = SDL_GetError();
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error_message);
    throw std::string(error_message);
  }

  return new Surface(sdl_surface_p);
}