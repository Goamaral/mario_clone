#include "Store.hpp"

Store::Store(/* args */) {
}

Store::~Store() {
  freeSurfaces();
  Texture::free(screen_texture);
  delete window_p;
}

void Store::freeSurfaces() {
  auto it = surfaces.begin();
  while (it != surfaces.end()) {
    Surface::free(*it);
    ++it;
  }
}

bool Store::load_media() {
  if (!load_surfaces()) return false;
  if (!load_textures()) return false;

  return true;
}

bool Store::load_textures() {
  screen_texture = Texture::load("resources/textures/texture.png", window_p->renderer_p);
  if (!screen_texture) return false;

  return true;
}

bool Store::load_surfaces() {
  if (!this->loadSurface(KEY_PRESS_SURFACE_DEFAULT, "resources/surfaces/default.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_UP, "resources/surfaces/up.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_DOWN, "resources/surfaces/down.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_LEFT, "resources/surfaces/left.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_RIGHT, "resources/surfaces/right.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_IMAGE, "resources/surfaces/image.png")) return false;

  return true;
}

bool Store::init(const char* title, int width, int height) {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    window_p = new Window(title, width, height);
    success = window_p->loaded;
  }

  return success;
}

bool Store::loadSurface(int index, std::string resource_path) {
  surfaces.push_back(Surface::loadOptimized(resource_path, window_p->surface_p));
  return surfaces.at(index) != NULL;
}