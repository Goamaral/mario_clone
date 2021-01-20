#include "07_texture_loading_and_rendering.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.init_png_img();
  system.create_window("main", WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

  try {
    system.load_texture_from_png("resources/images/texture.png", "texture", "main");
  } catch (std::string) {
    return 1;
  }

  system.render_texture("main", "texture");
  system.delay(2000);

  return 0;
}