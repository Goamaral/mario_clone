#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

class Game {
  public:
    Game(int width, int height, const char *title);
    ~Game();

    void main_loop();
    void draw();

  private:
    SDL_Window *window;
    SDL_Surface* screen_surface;
};