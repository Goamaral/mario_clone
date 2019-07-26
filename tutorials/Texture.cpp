#include "Texture.hpp"

texture_t::~texture_t() {
  if (p != NULL) texture_free(p);
}

texture_t::texture_t(SDL_Texture* p, int width, int height) {
  this->p = p;
  this->width = width;
  this->height = height;
  this->loaded = p != NULL;
}

void texture_free(SDL_Texture* texture_p) {
  SDL_DestroyTexture(texture_p);
}

texture_t* texture_load_from_file(std::string resource_path, SDL_Renderer* renderer_p, bool set_color_key, int r, int g, int b) {
  SDL_Texture* new_texture = NULL;
  int width = 0;
  int height = 0;

  SDL_Surface* loaded_surface = surface_load_from_image(resource_path);
  if (loaded_surface) {
    // Color key image
    if (set_color_key) SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, r, g, b));
    new_texture = SDL_CreateTextureFromSurface(renderer_p, loaded_surface);
    width = loaded_surface->w;
    height = loaded_surface->h;
    surface_free(loaded_surface);
  }

  return new texture_t(new_texture, width, height);
}
