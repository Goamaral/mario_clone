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
  KEY_PRESS_SURFACE_IMAGE
};

std::unordered_map<int, Texture> textures;
enum {
  VIEWPORT_TEXTURE,
  BACKGROUND_TEXTURE,
  PLAYER_TEXTURE,
  COLOR_MODULATION_TEXTURE
};

int main(int, char**);
bool init();
bool load_surface(int, std::string);
bool load_texture(int, std::string, Uint8 = 0x00, Uint8 = 0x00, Uint8 = 0x00);
bool load_media();
void run();
void close();
void game_loop();