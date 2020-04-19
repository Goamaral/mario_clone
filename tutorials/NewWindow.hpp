#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

// CUSTOM LIBS

#ifndef WINDOW_H
#define WINDOW_H

class Window {
  public:
    SDL_Window* $sdl_p;
    SDL_Renderer* $sdl_renderer_p;
    SDL_Surface* $sdl_surface_p;
    std::string $title;
    int $width;
    int $height;

    Window();
    ~Window();

    // Deallocates texture
    void free();
    bool init(std::string, int, int);
    void render_surface(SDL_Surface*);
    void sleep(int);
};

#endif