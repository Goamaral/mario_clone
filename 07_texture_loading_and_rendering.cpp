#include "07_texture_loading_and_rendering.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.init_png_img();
  std::shared_ptr<Window> main_window_p = system.create_window("main", WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

  try {
    main_window_p->load_texture_from_png("resources/images/texture.png", "texture");
  } catch (std::string) {
    return 1;
  }

  main_window_p->render_texture("texture");
  system.delay(2000);

  return 0;
}