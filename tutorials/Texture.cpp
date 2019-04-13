#include "Texture.hpp"

/***** CONSTRUCTOR *****/
Texture::Texture() {
}

/***** DESTRUCTOR *****/
Texture::~Texture() {

}

/***** STATIC *****/
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
    Surface::free(loaded_surface);
  }

  return new_texture;
}

void Texture::free(SDL_Texture* texture_p) {
  SDL_DestroyTexture(texture_p);
}

/***** METHODS *****/
SDL_Texture* Texture::loadFromFile(std::string path, SDL_Renderer* renderer_p) {
  SDL_Texture* new_texture = NULL;

  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (!loaded_surface) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  } else {
    // Color key image
    SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF ));
    new_texture = SDL_CreateTextureFromSurface(renderer_p, loaded_surface);
  }

  return new_texture;
}
