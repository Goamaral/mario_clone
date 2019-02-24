#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H
#include <SDL2/SDL_image.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef WINDOW_SURFACE_H
#define WINDOW_SURFACE_H
#include "WindowSurface.cpp"
#endif

class Surface {
  private:
  public:
    Surface(/* args */);
    ~Surface();

    static SDL_Surface* loadOptimized(std::string, WindowSurface*);
    static SDL_Surface* loadFromImage(std::string);
    static void free(SDL_Surface*);
};

SDL_Surface* loadOptimized(std::string resource_path, WindowSurface* window_surface_p) {
  // Optimized image
	SDL_Surface* optimized_surface = NULL;

  // Load surface image
  SDL_Surface* loaded_surface = loadFromImage(resource_path);

  if (loaded_surface) {
    // Convert surface to screen format
		optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface_p->pointer->format, 0);

    if (!optimized_surface) {
			printf("Unable to optimize image %s SDL Error: %s\n", resource_path.c_str(), SDL_GetError());
		}

		// Free old loaded surface
		SDL_FreeSurface(loaded_surface);
  }

  return optimized_surface;
}

SDL_Surface* loadFromImage(std::string image_location) {
  SDL_Surface* loaded_surface = IMG_Load(image_location.c_str());

  if (!loaded_surface) {
    printf("Failed to load image %s SDL Error: %s\n", image_location.c_str(), IMG_GetError());
  }

  return loaded_surface;
}

void free(SDL_Surface* surface_p) {
  SDL_FreeSurface(surface_p);
}