#include "System.hpp"

int main(int argc, char** args) {
  int window_width = 640;
  int window_height = 480;

  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", "SDL Tutorial", window_width, window_height);

  system.window("main")->renderer_reset();
  system.window("main")->render_rectangle(window_width / 4, window_height / 4, window_width / 2, window_height / 2, Color("red"));
  system.window("main")->render_rectangle_outline(window_width / 6, window_height / 6, window_width * 2 / 3, window_height * 2 / 3, Color("green"));
  system.window("main")->render_line(0, window_height / 2, window_width, window_height / 2, Color("blue"));
  for (int i = 0; i < window_height; i += 4) system.window("main")->render_point(window_width / 2, i, Color("yellow"));
  system.window("main")->renderer_render();
  system.delay(2000);

  return 0;
}