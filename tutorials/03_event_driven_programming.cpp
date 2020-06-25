#include "03_event_driven_programming.hpp"

int main(int argc, char** args) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
    return 1;
  } else {
    event_loop();
    SDL_Quit();
    return 0;
  }
}

void event_loop() {
  SDL_Event event;
  Window window;
  window.init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT); // FUTURE: Write to STDERR if false returned

  while (true) {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        // User requests quit
        case SDL_QUIT:
          return;
        // User presses a key
        case SDL_KEYDOWN:
          // Select surfaces based on key press
          switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
              return;
          }
          break;

        default:
          printf("Unhandled event with type %d\n", event.type);
      }
    } else {
      printf("No events to handle\n");
    }
  }
}