#include "NewWindow.hpp"

Window::Window() {
  $sdl_p = NULL;
  $sdl_renderer_p = NULL; // FUTURE: Renderer class
  $sdl_surface_p = NULL; // FUTURE: Surface class
}

Window::~Window() {
  if ($sdl_surface_p) {
    SDL_FreeSurface($sdl_surface_p); // FUTURE: Surface class
    IMG_Quit();
  }
  if ($sdl_renderer_p) SDL_DestroyRenderer($sdl_renderer_p);// FUTURE: Renderer class
  if ($sdl_p) SDL_DestroyWindow($sdl_p);
}

bool Window::init(std::string title, int width, int height) {
  $title = title;
  $width = width;
  $height = height;
  $sdl_p = SDL_CreateWindow($title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, $width, $height, SDL_WINDOW_SHOWN);

  if ($sdl_p == NULL) {
    printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  $sdl_renderer_p = SDL_CreateRenderer($sdl_p, -1, SDL_RENDERER_ACCELERATED); // FUTURE: Renderer class

  if ($sdl_renderer_p == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor($sdl_renderer_p, 0xFF, 0xFF, 0xFF, 0xFF); // FUTURE: Renderer class

  // Initialize PNG loading
  int img_flags = IMG_INIT_PNG;

  if ((IMG_Init(IMG_INIT_PNG) & img_flags) != img_flags) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    return false;
  }

  // Check window surface
  $sdl_surface_p = SDL_GetWindowSurface($sdl_p); // FUTURE: Surface class

  return $sdl_surface_p != NULL;
}

void Window::render_surface(SDL_Surface* sdl_surface_p) {
  // Apply the image
  SDL_BlitSurface(sdl_surface_p, NULL, $sdl_surface_p, NULL);
  // Update the surface
  SDL_UpdateWindowSurface($sdl_p);
}

void Window::sleep(int secs) {
  SDL_Delay(secs * 1000);
}