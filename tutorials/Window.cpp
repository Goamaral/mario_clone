#include "Window.hpp"

Window::Window() {}

Window::Window(std::string title, int width, int height) {
  p = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN
  );

  if (p) {
    // Window Renderer
    renderer_p = SDL_CreateRenderer(p, -1, SDL_RENDERER_ACCELERATED);

    // Initialize renderer color
    if (renderer_p)  {
      SDL_SetRenderDrawColor(renderer_p, 0xFF, 0xFF, 0xFF, 0xFF);

      // Initialize PNG loading
      int img_flags = IMG_INIT_PNG;

      if(!!(IMG_Init(img_flags) & img_flags)) {
        // Check window surface
        surface_p = SDL_GetWindowSurface(p);
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

Window::~Window() {
  if (surface_p) Surface::free(surface_p);
  if (renderer_p) SDL_DestroyRenderer(renderer_p);
  if (p) SDL_DestroyWindow(p);
}

void Window::render_surface(SDL_Surface* surface_to_render_p) {
  // Apply the image
  SDL_BlitSurface(surface_to_render_p, NULL, surface_p, NULL);

  // Update the surface
  SDL_UpdateWindowSurface(p);
}

void Window::render_texture(SDL_Texture* texture_to_render_p) {
  SDL_RenderCopy(renderer_p, texture_to_render_p, NULL, NULL);
}

void Window::set_viewport(SDL_Rect* viewport_p) {
  SDL_RenderSetViewport(renderer_p, viewport_p);
}

void Window::render_viewports() {
  SDL_RenderPresent(renderer_p);
}