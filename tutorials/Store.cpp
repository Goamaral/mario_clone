#ifndef MEMORY_H
#define MEMORY_H
#include <memory>
#endif

#ifndef WINDOW_H
#define WINDOW_H
#include "Window.cpp"
#endif

#ifndef WINDOW_SURFACE_H
#define WINDOW_SURFACE_H
#include "WindowSurface.cpp"
#endif

#ifndef WINDOW_RENDERER_H
#define WINDOW_RENDERER_H
#include "WindowRenderer.cpp"
#endif

#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
#endif

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.cpp"
#endif

#ifndef TEXTURE_H
#define TEXTURE_H
#include "Texture.cpp"
#endif

enum {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_IMAGE,
  KEY_PRESS_SURFACE_TOTAL
};

class Store {
  private:
  public:
    Store(/* args */);
    ~Store();

    Window* window_p = NULL;
    std::vector<SDL_Surface*> surfaces;

    bool init();
    bool load_media();
    bool load_textures();
    bool load_surfaces();
    bool loadSurface(int, std::string);
};

Store::Store(/* args */) {
  printf("OPENING STORE\n");
  surfaces.reserve(KEY_PRESS_SURFACE_TOTAL);
}

Store::~Store() {
  printf("CLOSING STORE\n");

  delete window_p;
}

bool Store::load_media() {
  if (!this->load_surfaces()) return false;

  if (!this->load_textures()) return false;

  return true;
}

bool Store::load_textures() {
  screen_texture = Texture::load("resources/textures/texture.png");
  if (!screen_texture) return false;

  return true;
}

bool Store::load_surfaces() {
  if (!this->loadSurface(KEY_PRESS_SURFACE_DEFAULT, "resources/surfaces/default.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_UP, "resources/surfaces/up.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_DOWN, "resources/surfaces/down.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_LEFT, "resources/surfaces/left.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_RIGHT, "resources/surfaces/right.bmp")) return false;
  if (!this->loadSurface(KEY_PRESS_SURFACE_IMAGE, "resources/surfaces/image.bmp")) return false;

  return true;
}

bool Store::init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    window_p = new Window("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT);
    success = window_p->loaded;
  }

  return success;
}

bool Store::loadSurface(int index, std::string resource_path) {
  surfaces.at(index) = Surface::loadOptimized(resource_path, window_p->surface_p);
  return surfaces.at(index) != NULL;
}