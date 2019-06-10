#include "Surface.hpp"

SDL_Surface* surface_load_optimized(std::string resource_path, SDL_Surface* surface_p) {
  // Optimized image
  SDL_Surface* optimized_surface = NULL;

  // Load surface image
  SDL_Surface* loaded_surface = surface_load_from_image(resource_path);

  if (loaded_surface) {
    // Convert surface to screen format
    optimized_surface = SDL_ConvertSurface(loaded_surface, surface_p->format, 0);

    if (!optimized_surface) {
      printf("Unable to optimize image %s SDL Error: %s\n", resource_path.c_str(), SDL_GetError());
    }

    // Free old loaded surface
    SDL_FreeSurface(loaded_surface);
  }

  return optimized_surface;
}

SDL_Surface* surface_load_from_image(std::string image_location) {
  SDL_Surface* loaded_surface = IMG_Load(image_location.c_str());

  if (!loaded_surface) {
  printf("Failed to load image %s SDL Error: %s\n", image_location.c_str(), IMG_GetError());
  }

  return loaded_surface;
}

void surface_free(SDL_Surface* surface_p) {
  SDL_FreeSurface(surface_p);
}