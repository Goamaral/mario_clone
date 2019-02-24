#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H
#include <SDL2/SDL_image.h>
#endif

#ifndef SDTIO_H
#define SDTIO_H
#include <cstdio>
#endif

#ifndef SURFACE_H
#define SURFACE_H
#include "Surface.cpp"
#endif

class Texture {
  public:
    Texture(SDL_Renderer* screen_renderer);
    ~Texture();

    int width = 0;
    int height = 0;

    static SDL_Texture* load(std::string, SDL_Renderer*);
    bool loadFromFile(std::string path);
    void render(int x, int y);
    void free(std::string);

  private:
    SDL_Texture* texture = NULL;
    SDL_Renderer* screen_renderer = NULL;
};

Texture::Texture(SDL_Renderer* screen_renderer) {
  this->screen_renderer = screen_renderer;
}

SDL_Texture* Texture::load(std::string resource_path, SDL_Renderer* renderer) {
  // Final texture
  SDL_Texture* new_texture;

  // Load texture image
  SDL_Surface* loaded_surface = Surface::loadFromImage(resource_path);

  if (loaded_surface) {
    // Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

    if (!new_texture) {
      printf("Unable to create texture from %s! SDL Error: %s\n", resource_path.c_str(), SDL_GetError());
    }

    // Free surface
    SDL_FreeSurface(loaded_surface);
  }

  return new_texture;
}

bool Texture::loadFromFile(std::string path) {
  free();

  SDL_Texture* new_texture = NULL;

  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (!loaded_surface) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  } else {
    // Color key image
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF ));
    new_texture = SDL_CreateTextureFromSurface(screen_renderer, loaded_surface);
  }
}
