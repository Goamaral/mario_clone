#include "Window.hpp"

Window::Window(std::string title, int width, int height) {
  // Window
  pointer = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN
  );

  if (pointer) {
    // Window Renderer
    renderer_p = loadRenderer();

    // Initialize renderer color
    if (renderer_p)  {
      SDL_SetRenderDrawColor(renderer_p, 0xFF, 0xFF, 0xFF, 0xFF);

      // Initialize PNG loading
      int img_flags = IMG_INIT_PNG;

      if(!!(IMG_Init(img_flags) & img_flags)) {
        // Get window surface
        surface_p = loadSurface();

        if (surface_p) loaded = true;
      } else {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
      }

    } else {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
  } else {
    printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
  }
}

SDL_Renderer* Window::loadRenderer() {
  return SDL_CreateRenderer(pointer, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Surface* Window::loadSurface() {
  return SDL_GetWindowSurface(pointer);
}

void Window::render_surface(SDL_Surface* surface_to_render_p) {
  // Apply the image
  SDL_BlitSurface(surface_to_render_p, NULL, surface_p, NULL);

  // Update the surface
  SDL_UpdateWindowSurface(pointer);
}

Window::~Window() {
  if (surface_p) Surface::free(surface_p);
  if (renderer_p) SDL_DestroyRenderer(renderer_p);
  if (pointer) SDL_DestroyWindow(pointer);
}