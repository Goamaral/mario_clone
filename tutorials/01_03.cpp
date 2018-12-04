// 01_hello_SDL
// 02_getting_an_image_on_the_screen
// 03_event_driven_programming

#include <SDL2/SDL.h>
#include <stdio.h>

// Starts up SDL and creates window
bool init(SDL_Window* &screen_window, SDL_Surface* &screen_surface);

// Loads media
bool load_media(SDL_Surface* &image_surface, const char* image_location);

// Frees media and shuts down SDL
void close(SDL_Surface* &image_surface_02, SDL_Surface* &image_surface_03, SDL_Window* &screen_window);

void game_loop(SDL_Surface* &image_surface, SDL_Surface* &screen_surface, SDL_Window* &screen_window);

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main (int argc, char **args) {
  SDL_Window* screen_window = NULL; // The window we'll be rendering to  
  SDL_Surface* screen_surface = NULL; // The surface contained by the window
  SDL_Surface* image_surface_02 = NULL; // The image we will load and show on the screen
  SDL_Surface* image_surface_03 = NULL; // The image we will load and show on the screen

  // Start up SDL and create window
  if (!init(screen_window, screen_surface)) {
    printf("Failed to initialize!\n");
  } else {
    bool media_loaded = load_media(image_surface_02, "resources/02.bmp") \
                        && load_media(image_surface_03, "resources/03.bmp");

    if (!media_loaded) {
      printf("Failed to load media!\n");
    } else {
      // Apply the image
      SDL_BlitSurface(image_surface_02, NULL, screen_surface, NULL);
      
      // Update surface
      SDL_UpdateWindowSurface(screen_window);

      // Wait 2 seconds
      SDL_Delay(2000);

      game_loop(image_surface_03, screen_surface, screen_window);
    }
  }

  // Free resources and close SDL
  close(image_surface_02, image_surface_03, screen_window);

  return 0;
}

bool init(SDL_Window* &screen_window, SDL_Surface* &screen_surface) {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    screen_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, \
      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN \
    );
    
    if (!screen_window) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Get window surface
      screen_surface = SDL_GetWindowSurface(screen_window);
    }
  }

  return success;
}

bool load_media(SDL_Surface* &image_surface, const char* image_location) {
  // Loading success flag
  bool success = true;

  // Load splash image
  image_surface = SDL_LoadBMP(image_location);
  
  if (!image_surface) {
    printf("Unable to load image %s! SDL Error: %s\n", image_location, SDL_GetError());
    success = false;
  }

  return success;
}

void close(SDL_Surface* &image_surface_02, SDL_Surface* &image_surface_03, SDL_Window* &screen_window) {
  // Deallocate surface
  SDL_FreeSurface(image_surface_02);
  image_surface_02 = NULL;

  SDL_FreeSurface(image_surface_03);
  image_surface_03 = NULL;

  // Destroy window
  SDL_DestroyWindow(screen_window);
  screen_window = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

void game_loop(SDL_Surface* &image_surface, SDL_Surface* &screen_surface, SDL_Window* &screen_window) {
  // Game loop flag
  bool quit = false;

  // Event object
  SDL_Event ev;

  // While application is running
  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&ev)) {
      // User requests quit
      if (ev.type == SDL_QUIT) {
        quit = true;
      }
    }

    // Apply the image
    SDL_BlitSurface(image_surface, NULL, screen_surface, NULL);

    // Update the surface
    SDL_UpdateWindowSurface(screen_window);
  }
}