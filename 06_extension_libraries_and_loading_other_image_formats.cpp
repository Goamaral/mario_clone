#include "System.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", "SDL Tutorial", 640, 480);

  try {
    system.load_surface_from_png("resources/images/png_loaded.png", "png_loaded", "main");
  } catch (std::string) {
    return 1;
  }

  system.render_surface("main", "png_loaded");
  system.delay(2000);

  return 0;
}