#include "engine.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

  system.window("main")->renderer_reset();
  system.window("main")->render_rectangle(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, Color("red"));
  system.window("main")->render_rectangle_outline(WINDOW_WIDTH / 6, WINDOW_HEIGHT / 6, WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT * 2 / 3, Color("green"));
  system.window("main")->render_line(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, Color("blue"));
  for (int i = 0; i < WINDOW_HEIGHT; i += 4) system.window("main")->render_point(WINDOW_WIDTH / 2, i, Color("yellow"));
  system.window("main")->renderer_render();
  system.delay(2000);

  return 0;
}