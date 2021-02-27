#include "System.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", "SDL Tutorial", 640, 480);

  try {
    system.load_surface_from_bmp("resources/images/stretch.bmp", "stretch", "main");
  } catch (std::string) {
    return 1;
  }

  system.render_surface("main", "stretch");
  system.delay(2000);

  system.render_surface("main", "stretch", true);
  system.delay(2000);

  return 0;
}