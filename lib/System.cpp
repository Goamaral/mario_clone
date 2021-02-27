#include "System.hpp"

System::System() {
  $sdl_inited = false;
  $sdl_img_inited = false;
}

System::~System() {
  $windows.clear();
  $surfaces.clear();
  $textures.clear();

  if ($sdl_img_inited) IMG_Quit();
  if ($sdl_inited) SDL_Quit();
}

// STATIC METHODS

// INSTANCE METHODS
// GENERAL
void System::init(Uint32 flags) {
  SDL_assert(SDL_Init(flags) == 0);
  $sdl_inited = true;
}

void System::init_png_img() {
  if (!$sdl_png_img_inited) {
    SDL_assert((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG);
    $sdl_png_img_inited = true;
    $sdl_img_inited = true;
  }
}

void System::delay(Uint32 ms) {
  SDL_Delay(ms);
}

// WINDOWS
std::shared_ptr<Window> System::create_window(std::string key, std::string title, int width, int height) {
  std::shared_ptr<Window> window_p(new Window());

  window_p->init(title, width, height);
  $windows.insert({ key, window_p });

  return window_p;
}

// SURFACES
std::shared_ptr<Surface> System::load_surface_from_bmp(std::string image_location, std::string key, std::string window_key) {
  SDL_PixelFormat* sdl_pixel_format_p = NULL;
  
  std::shared_ptr<Window> window_p = $windows.at(window_key);
  sdl_pixel_format_p = window_p->surface_pixel_format();

  std::shared_ptr<Surface> surface_p(Surface::load_from_bmp(image_location, sdl_pixel_format_p));

  $surfaces.insert({ key, surface_p });

  return surface_p;
}

std::shared_ptr<Surface> System::load_surface_from_png(std::string image_location, std::string key, std::string window_key) {
  init_png_img();

  SDL_PixelFormat *sdl_pixel_format_p = NULL;

  std::shared_ptr<Window> window_p = $windows.at(window_key);
  sdl_pixel_format_p = window_p->surface_pixel_format();

  std::shared_ptr<Surface> surface_p(Surface::load_from_png(image_location, sdl_pixel_format_p));

  $surfaces.insert({key, surface_p});

  return surface_p;
}

void System::render_surface(std::string window_key, std::string surface_key, bool scaled) {
  std::shared_ptr<Window> window_p = $windows.at(window_key);
  std::shared_ptr<Surface> surface_p = $surfaces.at(surface_key);

  window_p->render_surface(surface_p.get(), scaled);
}

// TEXTURES
std::shared_ptr<Texture> System::load_texture_from_png(std::string image_location, std::string key, std::string window_key) {
  init_png_img();

  std::shared_ptr<Window> window_p = $windows.at(window_key);
  std::shared_ptr<Texture> texture_p(Texture::load_from_png(image_location, window_p->sdl_renderer_p()));

  $textures.insert({key, texture_p});

  return texture_p;
}

void System::render_texture(std::string window_key, std::string texture_key) {
  std::shared_ptr<Window> window_p = $windows.at(window_key);
  std::shared_ptr<Texture> texture_p = $textures.at(texture_key);

  window_p->render_texture(texture_p.get());
}

// GETTERS
std::shared_ptr<Window> System::window(std::string window_key) {
  return $windows.at(window_key);
}