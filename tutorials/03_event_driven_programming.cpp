#include "03_event_driven_programming.hpp"

int main(int argc, char** args) {
  System system;
  system.init(SDL_INIT_VIDEO);
  system.create_window("main", WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

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
            running = false;
            break;
        }
        break;
    }
  }

  return 0;
}