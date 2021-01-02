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
  int result = SDL_SetRenderDrawColor($sdl_renderer_p, 0x00, 0x00, 0x00, 0x00);
  SDL_assert(result == 0);

  result = SDL_RenderSetViewport($sdl_renderer_p, NULL);
  SDL_assert(result == 0);

  result = SDL_RenderClear($sdl_renderer_p);
  SDL_assert(result == 0);

  SDL_RenderPresent($sdl_renderer_p);
}

// SURFACES
void Window::render_surface(Surface* surface_p, bool scaled) {
  int result = 0;

  if (scaled) {
    result = SDL_BlitScaled(surface_p->sdl_p(), NULL, $sdl_surface_p, NULL); // TODO: Surface::copy_scaled(SDL_Surface* destination, SDL_Surface* target)
  } else {
    result = SDL_BlitSurface(surface_p->sdl_p(), NULL, $sdl_surface_p, NULL); // TODO: Surface::copy(SDL_Surface* destination, SDL_Surface* target)
  }

  SDL_assert(result == 0);

  result = SDL_UpdateWindowSurface($sdl_p);
  SDL_assert(result == 0);
}

// TEXTURES
// NOTE: Move this to system
std::shared_ptr<Texture> Window::load_texture_from_png(std::string image_location, std::string key) {
  std::unique_ptr<Surface> surface_p(Surface::load_from_png(image_location));

  // NOTE: Move this static texture method
  SDL_Texture* sdl_texture_p = SDL_CreateTextureFromSurface($sdl_renderer_p, surface_p->sdl_p());
  SDL_assert(sdl_texture_p != NULL);

  Texture* raw_texture_p = new Texture(sdl_texture_p, surface_p->width(), surface_p->height());

  std::shared_ptr<Texture> texture_p(raw_texture_p);

  $textures.insert({key, texture_p});

  return texture_p;
}

void Window::render_texture(std::string texture_key) {
   std::shared_ptr<Texture> texture_p = $textures.at(texture_key);
  int result = SDL_RenderCopy($sdl_renderer_p, texture_p->sdl_p(), NULL, NULL);
  SDL_assert(result == 0);
}

// GETTERS
SDL_PixelFormat* Window::surface_pixel_format() {
  return $sdl_surface_p->format;
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