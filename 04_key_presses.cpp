#include "System.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", "SDL Tutorial", 640, 480);

  try {
    system.load_surface_from_bmp("resources/images/default.bmp", "default", "main");
    system.load_surface_from_bmp("resources/images/up.bmp", "up", "main");
    system.load_surface_from_bmp("resources/images/down.bmp", "down", "main");
    system.load_surface_from_bmp("resources/images/left.bmp", "left", "main");
    system.load_surface_from_bmp("resources/images/right.bmp", "right", "main");
  } catch (std::string) {
    return 1;
  }

  system.render_surface("main", "default");

  SDL_Event event;
  bool running = true;

  while (running) {
    SDL_PollEvent(&event);

    switch (event.type) {
      case SDL_QUIT:
        running = false;
        break;

      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
            running =  false;
            break;

          case SDLK_UP:
            system.render_surface("main", "up");
            break;

          case SDLK_DOWN:
            system.render_surface("main", "down");
            break;

          case SDLK_LEFT:
            system.render_surface("main", "left");
            break;

          case SDLK_RIGHT:
            system.render_surface("main", "right");
            break;

          default:
            system.render_surface("main", "default");
            break;
        }
      break;
    }
  }

  return 0;
}