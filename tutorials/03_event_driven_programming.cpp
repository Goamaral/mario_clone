#include "03_event_driven_programming.hpp"

int main(int argc, char** args) {
  System system;

  system.init(SDL_INIT_VIDEO);

  std::shared_ptr<Window> window_p = system.create_window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
  
  system.event_loop([](SDL_Event event) {
    switch (event.type) {
      case SDL_QUIT:
        return false;

      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
            return false;
        }
        break;
    }

    return true;
  });

  return 0;
}