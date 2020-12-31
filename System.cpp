#include "System.hpp"

System::System() {
  $sdl_inited = false;
  $sdl_img_inited = false;
}

System::~System() {
  $windows.clear();
  $surfaces.clear();

  if ($sdl_img_inited) IMG_Quit();
  if ($sdl_inited) SDL_Quit();
}

void System::init(Uint32 flags) {
  SDL_assert(SDL_Init(flags) == 0);
  $sdl_inited = true;
}

std::shared_ptr<Window> System::create_window(std::string key, std::string title, int width, int height) {
  std::shared_ptr<Window> window_p(new Window());

  window_p->init(title, width, height);
  $windows.insert({ key, window_p });

  return window_p;
}

void System::delay(Uint32 ms) {
  SDL_Delay(ms);
}

std::shared_ptr<Surface> System::load_surface_from_bmp(std::string key, std::string image_location, std::string window_key) {
  SDL_PixelFormat* sdl_pixel_format_p = NULL;
  
  if (window_key != "") {
    std::shared_ptr<Window> window_p = $windows.at(window_key);
    sdl_pixel_format_p = window_p->surface_pixel_format();
  }

  std::shared_ptr<Surface> surface_p(Surface::load_from_bmp(image_location, sdl_pixel_format_p));

  $surfaces.insert({ key, surface_p });

  return surface_p;
}

std::shared_ptr<Surface> System::load_surface_from_png(std::string key, std::string image_location, std::string window_key) {
  if (!$sdl_png_img_inited) {
    SDL_assert((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG);
    $sdl_png_img_inited = true;
    $sdl_img_inited = true;
  }

  SDL_PixelFormat *sdl_pixel_format_p = NULL;

  if (window_key != "") {
    std::shared_ptr<Window> window_p = $windows.at(window_key);
    sdl_pixel_format_p = window_p->surface_pixel_format();
  }

  std::shared_ptr<Surface> surface_p(Surface::load_from_png(image_location, sdl_pixel_format_p));

  $surfaces.insert({key, surface_p});

  return surface_p;
}

void System::render_surface(std::string window_key, std::string surface_key, bool scaled) {
  std::shared_ptr<Window> window_p = $windows.at(window_key);
  std::shared_ptr<Surface> surface_p = $surfaces.at(surface_key);

  window_p->render_surface(surface_p.get(), scaled);
}