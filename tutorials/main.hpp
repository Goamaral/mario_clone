#include <SDL2/SDL.h>

#include <memory>
#include <cstdio>
#include <string>

#include "Store.hpp"

void run();

// Starts up SDL and creates window
bool init(Store&);

// Load image
SDL_Surface* load_image(std::string);

// Load image to surface
SDL_Surface* load_surface(std::string);

// Load image to texture
SDL_Texture* load_texture(std::string);

// Load surface images
bool load_surfaces(Store&);

// Load texture images
bool load_textures();

// Load surface and texture images
bool load_media(Store&);

// Frees media and shuts down SDL
void close();

// Game event loop
void game_loop(Store*);

// Render surface
void render_surface();

// Render texture
void render_texture();

// Render geometry
void render_geometry();

void render_viewport();