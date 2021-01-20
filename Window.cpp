#include "Window.hpp"

Window::Window() {
  $sdl_p = NULL;
  $sdl_renderer_p = NULL;
  $sdl_surface_p = NULL;
}

Window::~Window() {
  if ($sdl_surface_p) SDL_FreeSurface($sdl_surface_p);
  if ($sdl_renderer_p) SDL_DestroyRenderer($sdl_renderer_p);
  if ($sdl_p) SDL_DestroyWindow($sdl_p);
}

// STATIC METHODS

// INSTANCE METHODS
// GENERAL
void Window::init(std::string title, int width, int height) {
  $title = title;
  $width = width;
  $height = height;

  $sdl_p = SDL_CreateWindow($title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, $width, $height, SDL_WINDOW_SHOWN);
  SDL_assert($sdl_p != NULL);

  $sdl_renderer_p = SDL_CreateRenderer($sdl_p, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
  SDL_assert($sdl_renderer_p != NULL);

  int result = SDL_SetRenderDrawColor($sdl_renderer_p, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_assert(result == 0);

  $sdl_surface_p = SDL_GetWindowSurface($sdl_p);
  SDL_assert($sdl_surface_p != NULL);
}

void Window::renderer_render() {
  SDL_RenderPresent($sdl_renderer_p);
}

void Window::renderer_reset() {
  int result = SDL_SetRenderDrawColor($sdl_renderer_p, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_assert(result == 0);

  result = SDL_RenderSetViewport($sdl_renderer_p, NULL);
  SDL_assert(result == 0);

  result = SDL_RenderClear($sdl_renderer_p);
  SDL_assert(result == 0);
}

// SURFACES
void Window::render_surface(Surface* surface_p, bool scaled) {
  if (scaled) {
    Surface::copy_scaled(surface_p->sdl_p(), $sdl_surface_p);
  } else {
    Surface::copy(surface_p->sdl_p(), $sdl_surface_p);
  }

  int result = SDL_UpdateWindowSurface($sdl_p);
  SDL_assert(result == 0);
}

// TEXTURES
void Window::render_texture(Texture* texture_p) {
  renderer_reset();

  int result = SDL_RenderCopy($sdl_renderer_p, texture_p->sdl_p(), NULL, NULL);
  SDL_assert(result == 0);

  renderer_render();
}

// GETTERS
SDL_PixelFormat* Window::surface_pixel_format() {
  return $sdl_surface_p->format;
}

SDL_Renderer* Window::sdl_renderer_p() {
  return $sdl_renderer_p;
}

// LEGACY
// void Window::renderer_apply_texture(Texture* texture_p, SDL_Rect render_area, SDL_Rect clipping_area) {
//   if (clipping_area.w <= 0) clipping_area.w = texture_p->width;
//   if (clipping_area.h <= 0) clipping_area.h = texture_p->height;

//   if (render_area.w <= 0) render_area.w = clipping_area.w;
//   if (render_area.h <= 0) render_area.h = clipping_area.h;

//   int result = SDL_RenderCopy($sdl_renderer_p, texture_p->pointer, &clipping_area, &render_area);
//   SDL_assert(result == 0);
// }