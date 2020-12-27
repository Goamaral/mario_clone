#include "05_optimized_surface_loading_and_soft_stretching.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

  try {
    system.load_surface_from_bmp("stretch", "resources/images/stretch.bmp", "main");
  } catch (std::string) {
    return 1;
  }

  system.render_surface("main", "stretch");
  system.delay(2000);

  system.render_surface("main", "stretch", true);
  system.delay(2000);

  return 0;
}