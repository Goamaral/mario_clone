#include "Window.hpp"

window_t* global_window_p = NULL;

bool window_init(std::string title, int width, int height) {
  global_window_p = new window_t;
  global_window_p->p = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN
  );

  if (global_window_p->p) {
    // Window Renderer
    global_window_p->renderer_p = SDL_CreateRenderer(global_window_p->p, -1, SDL_RENDERER_ACCELERATED);

    // Initialize renderer color
    if (global_window_p->renderer_p)  {
      SDL_SetRenderDrawColor(global_window_p->renderer_p, 0xFF, 0xFF, 0xFF, 0xFF);

      // Initialize PNG loading
      int img_flags = IMG_INIT_PNG;

      if(!!(IMG_Init(img_flags) & img_flags)) {
        // Check window surface
        global_window_p->surface_p = SDL_GetWindowSurface(global_window_p->p);
        if (global_window_p->surface_p) return true;

      } else {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
      }

    } else {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
  } else {
    printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
  }

  return false;
}

void window_destroy() {
  if (global_window_p) {
    if (global_window_p->surface_p) surface_free(global_window_p->surface_p);
    if (global_window_p->renderer_p) SDL_DestroyRenderer(global_window_p->renderer_p);
    if (global_window_p->p) SDL_DestroyWindow(global_window_p->p);
  }
}

void window_render_surface(SDL_Surface* surface_to_render_p) {
  // Apply the image
  SDL_BlitSurface(surface_to_render_p, NULL, global_window_p->surface_p, NULL);

  // Update the surface
  SDL_UpdateWindowSurface(global_window_p->p);
}

void window_render_texture(SDL_Texture* texture_to_render_p) {
  SDL_RenderCopy(global_window_p->renderer_p, texture_to_render_p, NULL, NULL);
}

void window_set_viewport(SDL_Rect* viewport_p) {
  SDL_RenderSetViewport(global_window_p->renderer_p, viewport_p);
}

void window_render_viewports() {
  SDL_RenderPresent(global_window_p->renderer_p);
}