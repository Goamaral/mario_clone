#include "NewWindow.hpp"

Window::Window() {
  $sdl_p = NULL;
  $sdl_renderer_p = NULL; // FUTURE: Renderer class
  $sdl_surface_p = NULL; // FUTURE: Surface class
}

Window::~Window() {
  if ($sdl_surface_p) SDL_FreeSurface($sdl_surface_p); // FUTURE: Surface class
  if ($sdl_renderer_p) SDL_DestroyRenderer($sdl_renderer_p);// FUTURE: Renderer class
  if ($sdl_p) SDL_DestroyWindow($sdl_p);
  IMG_Quit();
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

  $sdl_renderer_p = SDL_CreateRenderer($sdl_p, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // FUTURE: Renderer class

  if ($sdl_renderer_p == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor($sdl_renderer_p, 0xFF, 0xFF, 0xFF, 0xFF); // FUTURE: Renderer class

  // Initialize PNG loading
  int img_flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;

  if ((IMG_Init(img_flags) & img_flags) != img_flags) {
    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    return false;
  }

  // Check window surface
  $sdl_surface_p = SDL_GetWindowSurface($sdl_p); // FUTURE: Surface class

  return $sdl_surface_p != NULL;
}

void Window::render_surface(SDL_Surface* sdl_surface_p) {
  SDL_BlitSurface(sdl_surface_p, NULL, $sdl_surface_p, NULL);
  SDL_UpdateWindowSurface($sdl_p);
}

void Window::render_texture(Texture* texture_p, SDL_Rect render_area, SDL_Rect clipping_area) {
  if (clipping_area.w <= 0) clipping_area.w = texture_p->width;
  if (clipping_area.h <= 0) clipping_area.h = texture_p->height;

  if (render_area.w <= 0) render_area.w = clipping_area.w;
  if (render_area.h <= 0) render_area.h = clipping_area.h;

  SDL_RenderCopy($sdl_renderer_p, texture_p->pointer, &clipping_area, &render_area);
}

void Window::apply_renderer() {
  SDL_RenderPresent($sdl_renderer_p);
}

void Window::clear_renderer() {
  set_renderer_color(0x00, 0x00, 0x00, 0x00);
  set_renderer_viewport(NULL);
  SDL_RenderClear($sdl_renderer_p);
}

void Window::set_renderer_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor($sdl_renderer_p, r, g, b, a);
}

void Window::set_renderer_viewport(SDL_Rect* viewport_p) {
  SDL_RenderSetViewport($sdl_renderer_p, viewport_p);
}

void Window::sleep(int secs) {
  SDL_Delay(secs * 1000);
}