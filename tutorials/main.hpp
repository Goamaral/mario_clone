#include <SDL2/SDL.h>

#include <memory>
#include <cstdio>
#include <string>
#include <unordered_map>

#ifndef WINDOW_H
#define WINDOW_H
#include "Window.hpp"
#endif

#ifndef TEXTURE_H
#define TEXTURE_H
#include "Texture.hpp"
#endif

std::unordered_map<int, SDL_Surface*> surfaces;
enum {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_IMAGE,
  KEY_PRESS_SURFACE_TOTAL
};

std::unordered_map<int, SDL_Texture*> textures;
enum {
  LOADING_TEXTURE,
  VIEWPORT_TEXTURE
};

int main(int, char**);
bool init();
bool load_surface(int, std::string);
bool load_texture(int, std::string);
bool load_media();
void run();
void close();
void game_loop();