#include "System.hpp"

int main(int argc, char** args) {
  int window_width = 640;
  int window_height = 480;

  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", "SDL Tutorial", window_width, window_height);

  try {
    system.load_texture_from_png("resources/images/viewport.png", "viewport", "main");
  } catch (std::string) {
    return 1;
  }

  system.window("main")->renderer_reset();
  SDL_Rect top_left_viewport = { 0, 0, window_width / 2, window_height / 2 };
  system.window("main")->renderer_set_viewport(&top_left_viewport);
  system.render_texture("main", "viewport");
  SDL_Rect top_right_viewport = { window_width / 2, 0, window_width / 2, window_height / 2 };
  system.window("main")->renderer_set_viewport(&top_right_viewport);
  system.render_texture("main", "viewport");
  SDL_Rect bottom_viewport = { 0, window_height / 2, window_width, window_height / 2 };
  system.window("main")->renderer_set_viewport(&bottom_viewport);
  system.render_texture("main", "viewport");
  system.window("main")->renderer_render();
  system.delay(2000);

  return 0;
}