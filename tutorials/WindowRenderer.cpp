#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef WINDOW_H
#define WINDOW_H
#include "Window.cpp"
#endif

class WindowRenderer {
  public:
    WindowRenderer(Window* window_p);
    ~WindowRenderer();

    SDL_Renderer* pointer = NULL;
};

WindowRenderer::WindowRenderer(Window* window_p) {
  pointer = SDL_CreateRenderer(window_p->pointer, -1, SDL_RENDERER_ACCELERATED);
}

WindowRenderer::~WindowRenderer() {
  if (pointer) SDL_DestroyRenderer(pointer);
}
