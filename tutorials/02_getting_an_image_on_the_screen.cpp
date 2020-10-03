#include "02_getting_an_image_on_the_screen.hpp"

int main(int argc, char** args) {
  System system;

  system.init(SDL_INIT_VIDEO);
  system.init_img_support(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF);

  std::shared_ptr<Window> window_p = system.create_window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
  std::unique_ptr<Surface> surface_p (Surface::load_from_bmp("resources/surfaces/hello_world.bmp"));

  // If image could not be loaded terminate
  if (surface_p.get()->sdl_p == NULL) return 1;

  window_p->render_surface(surface_p.get());
  system.delay(2000);

  return 0;
}