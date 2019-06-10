#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

SDL_Surface* surface_load_optimized(std::string, SDL_Surface*);
SDL_Surface* surface_load_from_image(std::string);
void surface_free(SDL_Surface*);