#ifndef SDL_H
#define SDL_H
#include <SDL2/SDL.h>
#endif

#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H
#include <SDL2/SDL_image.h>
#endif

#ifndef SDTIO_H
#define SDTIO_H
#include <cstdio>
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef STORE_H
#define STORE_H
#include "Store.cpp"
#endif

/*
#ifndef TEXTURE_H
#define TEXTURE_H
#include "texture.cpp"
#endif
*/

enum {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_IMAGE,
  KEY_PRESS_SURFACE_TOTAL
};

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
void game_loop();

// Render surface
void render_surface();

// Render texture
void render_texture();

// Render geometry
void render_geometry();

void render_viewport();