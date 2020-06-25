#include "02_getting_an_image_on_the_screen.hpp"

int main(int argc, char** args) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
    return 1;
  } else {
    run();
    SDL_Quit();
    return 0;
  }
}

void run() {
  Window window;
  window.init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT); // FUTURE: Write to STDERR if false returned

  SDL_Surface* sld_surface_p = SDL_LoadBMP("resources/surfaces/hello_world.bmp");
  if (sld_surface_p == NULL) {
    SDL_FreeSurface(sld_surface_p);
    return;
  }

  window.render_surface(sld_surface_p);
  window.sleep(2);
}