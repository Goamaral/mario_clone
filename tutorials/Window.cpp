#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H
#include <SDL2/SDL_image.h>
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
    SDL_Renderer* renderer_p = NULL;
    SDL_Surface* surface_p = NULL;
    bool loaded = false;

    SDL_Renderer* loadRenderer();
    void freeRenderer();

    SDL_Surface* loadSurface();
    void freeSurface();
};

Window::Window(std::string title, int width, int height) {
  // Window
  pointer = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN
  );

  if (pointer) {
    // Window Renderer
    renderer_p = loadRenderer();

    // Initialize renderer color
    if (renderer_p)  {
      SDL_SetRenderDrawColor(renderer_p, 0xFF, 0xFF, 0xFF, 0xFF);

      // Initialize PNG loading
      int img_flags = IMG_INIT_PNG;

      if(!!(IMG_Init(img_flags) & img_flags)) {
        // Get window surface
        surface_p = loadSurface();

        if (surface_p) loaded = true;
      } else {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
      }

    } else {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
  } else {
    printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
  }
}

SDL_Renderer* Window::loadRenderer() {
  return SDL_CreateRenderer(pointer, -1, SDL_RENDERER_ACCELERATED);
}

void Window::freeRenderer() {
  if (renderer_p) SDL_DestroyRenderer(renderer_p);
}

SDL_Surface* Window::loadSurface() {
  return SDL_GetWindowSurface(pointer);
}

void Window::freeSurface() {
  if (renderer_p) SDL_FreeSurface(surface_p);
}

Window::~Window() {
  if (pointer) SDL_DestroyWindow(pointer);
  freeRenderer();
  freeSurface();
}