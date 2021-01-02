#include "Texture.hpp"

Texture::Texture(SDL_Texture* sdl_texture_p, int width, int height) {
  $sdl_p = sdl_texture_p;
  $width = width;
  $height = height;
}

Texture::~Texture() {
  if ($sdl_p) SDL_DestroyTexture($sdl_p);
}

// STATIC METHODS

// INSTANCE METHODS

// GETTERS
SDL_Texture* Texture::sdl_p() {
  return $sdl_p;
}

// LEGACY
// // Loads image at specified path
// bool Texture::load_from_file(std::string path, SDL_Renderer* renderer_p, Uint8 r, Uint8 g, Uint8 b) {
//   // Free preexisting texture
//   free();

//   SDL_Surface* loaded_surface = surface_load_from_image(path);
//   if (loaded_surface) {
//     // Color key image
//     SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, r, g, b));
    
//     // Create texture from surface
//     pointer = SDL_CreateTextureFromSurface(renderer_p, loaded_surface);
//     if (pointer != NULL) {
//       width = loaded_surface->w;
//       height = loaded_surface->h;
//     }
//     else {
//       printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//     }

//     surface_free(loaded_surface);
//   }

//   return pointer != NULL;
// }

// // Deallocates texture
// void Texture::free() {
//   // Free texture if it exists
//   if (pointer != NULL) {
//     SDL_DestroyTexture(pointer);
//     pointer = NULL;
//     width = 0;
//     height = 0;
//   }
// }

// // Set color modulation
// void Texture::set_modulation_color(Uint8 r, Uint8 g, Uint8 b) {
//   SDL_SetTextureColorMod(pointer, r, g, b);
// }

// // Set blending
// void Texture::set_blend_mode(SDL_BlendMode blending) {
//   SDL_SetTextureBlendMode(pointer, blending);
// }

// // Set alpha modulation
// void Texture::set_alpha(Uint8 a) {
//   SDL_SetTextureAlphaMod(pointer, a);
// }