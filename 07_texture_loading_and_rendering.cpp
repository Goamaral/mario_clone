#include "engine.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

  try {
    system.load_texture_from_png("resources/images/texture.png", "texture", "main");
  } catch (std::string) {
    return 1;
  }

  system.window("main")->renderer_reset();
  system.render_texture("main", "texture");
  system.window("main")->renderer_render();
  system.delay(2000);

  return 0;
}