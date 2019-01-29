#ifndef MEMORY_H
#define MEMORY_H
#include <memory>
#endif

#ifndef WINDOW_H
#define WINDOW_H
#include "Window.cpp"
#endif

#ifndef WINDOW_SURFACE_H
#define WINDOW_SURFACE_H
#include "WindowSurface.cpp"
#endif

#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H
#include "WindowRenderer.cpp"
#endif

#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif

#ifndef MAIN_H
#define MAIN_H
#include "main.hpp"
#endif

class Store {
  private:
  public:
    Store(/* args */);
    ~Store();

    Window* window_p = NULL;
    WindowRenderer* window_renderer_p = NULL;
    WindowSurface* window_surface_p = NULL;
    std::vector<SDL_Surface*> surfaces;

    bool buildWindow(std::string, int, int);
    bool buildWindowRenderer();
    bool buildWindowSurface();
    bool loadSurface(int, std::string);
};

Store::Store(/* args */) {
  printf("OPENING STORE\n");
  surfaces.reserve(KEY_PRESS_SURFACE_TOTAL);
}

Store::~Store() {
  printf("CLOSING STORE\n");

  delete window_p;
  delete window_renderer_p;
  delete window_surface_p;
}

bool Store::buildWindow(std::string title, int width, int height) {
  window_p = new Window(title, width, height);

  return window_p->pointer != NULL;
}

bool Store::buildWindowRenderer() {
  window_renderer_p = new WindowRenderer(window_p);

  // Initialize renderer color
  if (window_renderer_p) SDL_SetRenderDrawColor(window_renderer_p->pointer, 0xFF, 0xFF, 0xFF, 0xFF);

  return window_renderer_p->pointer != NULL;
}

bool Store::buildWindowSurface() {
  window_surface_p = new WindowSurface(window_p);

  return window_surface_p->pointer != NULL;
}

bool Store::loadSurface(int index, std::string resource_path) {
  // Optimized image
	SDL_Surface* optimized_surface = NULL;

  // Load surface image
  SDL_Surface* loaded_surface = load_image(resource_path);

  if (loaded_surface) {
    // Convert surface to screen format
		optimized_surface = SDL_ConvertSurface(loaded_surface, window_surface_p->pointer->format, 0);

    if (!optimized_surface) {
			printf("Unable to optimize image %s SDL Error: %s\n", resource_path.c_str(), SDL_GetError());
		}

		// Free old loaded surface
		SDL_FreeSurface(loaded_surface);
  }

  surfaces.at(index) = optimized_surface;

  return optimized_surface != NULL;
}