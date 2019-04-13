#include <string>
#include <vector>

#include "Window.hpp"
#include "Texture.hpp"

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
    SDL_Texture* screen_texture;

    bool init(const char *, int, int);
    bool load_media();
    bool load_textures();
    bool load_surfaces();
    bool loadSurface(int, std::string);

    void freeSurfaces();
};