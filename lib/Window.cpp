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

// RENDERER - Future Renderer class
void Window::renderer_render() {
  SDL_RenderPresent($sdl_renderer_p);
}

void Window::renderer_set_draw_color(Color color) {
  int result = SDL_SetRenderDrawColor($sdl_renderer_p, color.red, color.green, color.blue, color.alpha);
  SDL_assert(result == 0);
}

void Window::renderer_reset() {
  renderer_set_draw_color(Color(0));

  int result = SDL_RenderSetViewport($sdl_renderer_p, NULL);
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
  int result = SDL_RenderCopy($sdl_renderer_p, texture_p->sdl_p(), NULL, NULL);
  SDL_assert(result == 0);
}

void Window::render_rectangle(int x, int y, int width, int height, Color color) {
  SDL_Rect rectangle = { x, y, width, height };
  renderer_set_draw_color(color);

  int result = SDL_RenderFillRect($sdl_renderer_p, &rectangle);
  SDL_assert(result == 0);
}

void Window::render_rectangle_outline(int x, int y, int width, int height, Color color) {
  SDL_Rect rectangle = { x, y, width, height };
  renderer_set_draw_color(color);

  int result = SDL_RenderDrawRect($sdl_renderer_p, &rectangle);
  SDL_assert(result == 0);
}

void Window::render_line(int x1, int y1, int x2, int y2, Color color) {
  renderer_set_draw_color(color);

  int result = SDL_RenderDrawLine($sdl_renderer_p, x1, y1, x2, y2);
  SDL_assert(result == 0);
}

void Window::render_point(int x, int y, Color color) {
  renderer_set_draw_color(color);

  int result = SDL_RenderDrawPoint($sdl_renderer_p, x, y);
  SDL_assert(result == 0);
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