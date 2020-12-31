#include "NewSurface.hpp"

Surface::Surface(SDL_Surface* sdl_surface_p) {
  sdl_p = sdl_surface_p;
}

Surface::~Surface() {
  if (sdl_p) SDL_FreeSurface(sdl_p);
}

/* STATIC METHODS */
SDL_Surface* Surface::optimize_sdl_surface(SDL_Surface* sdl_surface_p, SDL_PixelFormat* sdl_pixel_format_p) {
  SDL_Surface* sdl_optimized_surface_p = SDL_ConvertSurface(sdl_surface_p, sdl_pixel_format_p, 0);

  if (sdl_optimized_surface_p != NULL) {
    SDL_FreeSurface(sdl_surface_p);
  } else {
    sdl_optimized_surface_p = sdl_surface_p;
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Surface optimization failed\n");
  }

  return sdl_optimized_surface_p;
}

Surface* Surface::load_from_bmp(std::string image_location, SDL_PixelFormat* sdl_pixel_format_p) {
  SDL_Surface* sdl_surface_p = SDL_LoadBMP(image_location.c_str());

  if (sdl_surface_p == NULL) {
    const char* error_message = SDL_GetError();
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error_message);
    throw std::string(error_message);
  }

  if (sdl_pixel_format_p != NULL) sdl_surface_p = Surface::optimize_sdl_surface(sdl_surface_p, sdl_pixel_format_p);

  return new Surface(sdl_surface_p);
}

Surface* Surface::load_from_png(std::string image_location, SDL_PixelFormat* sdl_pixel_format_p) {
  SDL_Surface* sdl_surface_p = IMG_Load(image_location.c_str());

  if (sdl_surface_p == NULL) {
    const char* error_message = SDL_GetError();
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error_message);
    throw std::string(error_message);
  }

  if (sdl_pixel_format_p != NULL) sdl_surface_p = Surface::optimize_sdl_surface(sdl_surface_p, sdl_pixel_format_p);

  return new Surface(sdl_surface_p);
}