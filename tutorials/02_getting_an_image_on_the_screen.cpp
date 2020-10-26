#include "02_getting_an_image_on_the_screen.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.init_img_support(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);
  system.create_window("main", WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

  try {
    system.load_surface_from_bmp("hello_world", "resources/images/hello_world.bmp");
  } catch (std::string) {
    return 1;
  }

  system.render_surface("main", "hello_world");
  system.delay(2000);

  return 0;
}