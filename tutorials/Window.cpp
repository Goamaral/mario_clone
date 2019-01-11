#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

class Window {
  public:
    Window(std::string, int, int);
    ~Window();

    SDL_Window* pointer = NULL;
};

Window::Window(std::string title, int width, int height) {
  pointer = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN
  );
}

Window::~Window() {
  if (pointer) SDL_DestroyWindow(pointer);
}
