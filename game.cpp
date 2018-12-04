#include "game.hpp"

// CONSTRUCTOR
Game::Game(int width, int height, const char *title) {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  this->screen_surface = SDL_GetWindowSurface(window);
}

// DECONSTRUCTOR
Game::~Game() {
  SDL_DestroyWindow(window);
  SDL_Quit();
}

// PUBLIC
void Game::main_loop() {
  //Shader shader("./shaders/basic");

  while (true) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
        case SDL_QUIT: return;
        case SDL_KEYDOWN:
          switch (e.key.keysym.sym) {
            case SDLK_ESCAPE: return;
            default: break;
          }
          break;
        default: break;
      }
    }

    this->draw();

    SDL_UpdateWindowSurface(window);
  }
}

void Game::draw() {
  SDL_FillRect(this->screen_surface, NULL, SDL_MapRGB(this->screen_surface->format, 0xFF, 0xFF, 0xFF ));
}