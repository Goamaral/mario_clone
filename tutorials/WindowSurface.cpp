#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef WINDOW_H
#define WINDOW_H
#include "Window.cpp"
#endif

class WindowSurface {
  public:
    WindowSurface(Window* window_p);
    ~WindowSurface();

    SDL_Surface* pointer = NULL;
};

WindowSurface::WindowSurface(Window* window_p) {
  pointer = SDL_GetWindowSurface(window_p->pointer);
}

WindowSurface::~WindowSurface() {
  if (pointer) SDL_FreeSurface(pointer);
}
