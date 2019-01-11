// 01_hello_SDL
// 02_getting_an_image_on_the_screen
// 03_event_driven_programming
// 04_key_presses
// 05_optimized_surface_loading_and_soft_stretching
// 06_loading_PNGs_with_SDL_image
// 07_texture_loading_and_rendering
// 08_geometry_rendering
// 09_the_viewport

#include "01_09.hpp"

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* screen_window = NULL; // Window we'll be rendering to
SDL_Surface* screen_surface = NULL; // Surface contained in the window
SDL_Renderer* screen_renderer = NULL; // Window renderer
SDL_Texture* screen_texture = NULL; // Window texture

SDL_Surface* key_press_surfaces[KEY_PRESS_SURFACE_TOTAL]; // Surfaces that correspond to a keypress
SDL_Surface* png_surface = NULL; // PNG surface
SDL_Surface* current_surface = NULL; // Selected surface

int main (int argc, char **args) {
  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
  } else {
    if (load_media()) {
      // Apply the image stretched
      SDL_Rect stretch_rect;
      stretch_rect.x = 0;
      stretch_rect.y = 0;
      stretch_rect.w = SCREEN_WIDTH;
      stretch_rect.h = SCREEN_HEIGHT;
      SDL_Surface* stretched_surface = load_surface("resources/surfaces/stretch.bmp");

      // Apply the image
      SDL_BlitScaled(stretched_surface, NULL, screen_surface, &stretch_rect);

      // Update the surface
      SDL_UpdateWindowSurface(screen_window);

      // Wait 2 seconds
      SDL_Delay(2000);

      SDL_FreeSurface(stretched_surface);

      game_loop();
    } else {
      printf("Failed to load media\n");
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}

bool init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window
    screen_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, \
      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN \
    );

    if (!screen_window) {
      printf("Window could not be created SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Create renderer for window
      screen_renderer = SDL_CreateRenderer(screen_window, -1, SDL_RENDERER_ACCELERATED);

      if (screen_renderer) {
        // Initialize renderer color
        SDL_SetRenderDrawColor(screen_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;

        if(!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = false;
        } else {
          // Get window surface
          screen_surface = SDL_GetWindowSurface(screen_window);
        }
      } else {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      }
    }
  }

  return success;
}

SDL_Surface* load_image(std::string image_location) {
  SDL_Surface* loaded_surface = IMG_Load(image_location.c_str());

  if (!loaded_surface) {
    printf("Failed to load image %s SDL Error: %s\n", image_location.c_str(), IMG_GetError());
  }

  return loaded_surface;
}

SDL_Surface* load_surface(std::string surface_location) {
  // Optimized image
	SDL_Surface* optimized_surface = NULL;

  // Load surface image
  SDL_Surface* loaded_surface = load_image(surface_location);

  if (loaded_surface) {
    // Convert surface to screen format
		optimized_surface = SDL_ConvertSurface(loaded_surface, screen_surface->format, 0);

    if (!optimized_surface) {
			printf("Unable to optimize image %s SDL Error: %s\n", surface_location.c_str(), SDL_GetError());
		}

		// Free old loaded surface
		SDL_FreeSurface(loaded_surface);
  }

  return optimized_surface;
}

SDL_Texture* load_texture(std::string texture_location) {
  // Final texture
  SDL_Texture* new_texture;

  // Load texture image
  SDL_Surface* loaded_surface = load_image(texture_location);

  if (loaded_surface) {
    // Create texture from surface pixels
    new_texture = SDL_CreateTextureFromSurface(screen_renderer, loaded_surface);

    if (!new_texture) {
      printf("Unable to create texture from %s! SDL Error: %s\n", texture_location.c_str(), SDL_GetError());
    }

    // Free surface
    SDL_FreeSurface(loaded_surface);
  }

  return new_texture;
}

bool load_surfaces() {
  key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT] = load_surface("resources/surfaces/default.bmp");
  if (!key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT]) return false;

  key_press_surfaces[KEY_PRESS_SURFACE_UP] = load_surface("resources/surfaces/up.bmp");
  if (!key_press_surfaces[KEY_PRESS_SURFACE_UP]) return false;

  key_press_surfaces[KEY_PRESS_SURFACE_DOWN] = load_surface("resources/surfaces/down.bmp");
  if (!key_press_surfaces[KEY_PRESS_SURFACE_DOWN]) return false;

  key_press_surfaces[KEY_PRESS_SURFACE_LEFT] = load_surface("resources/surfaces/left.bmp");
  if (!key_press_surfaces[KEY_PRESS_SURFACE_LEFT]) return false;

  key_press_surfaces[KEY_PRESS_SURFACE_RIGHT] = load_surface("resources/surfaces/right.bmp");
  if (!key_press_surfaces[KEY_PRESS_SURFACE_RIGHT]) return false;

  png_surface = load_surface("resources/surfaces/image.png");
  if (!png_surface) return false;

  return true;
}

bool load_textures() {
  screen_texture = load_texture("resources/textures/texture.png");
  if (!screen_texture) return false;

  return true;
}

bool load_media() {
  if (!load_surfaces()) return false;

  if (!load_textures()) return false;

  return true;
}

void close() {
  // Free texture
  SDL_DestroyTexture(screen_texture);
  screen_texture = NULL;

  // Free surfaces
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
    SDL_FreeSurface(key_press_surfaces[i]);
    key_press_surfaces[i] = NULL;
  }

  // Destroy renderer
  SDL_DestroyRenderer(screen_renderer);
  screen_renderer = NULL;

  // Destroy window
  SDL_DestroyWindow(screen_window);
  screen_window = NULL;

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void game_loop() {
  // Event object
  SDL_Event ev;

  // Set default surface
  current_surface = key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];

  // While application is running
  while (true) {
    // Handle events on queue
    while (SDL_PollEvent(&ev)) {
      switch (ev.type) {
        // User requests quit
        case SDL_QUIT:
          return;
        // User presses a key
        case SDL_KEYDOWN:
          // Select surfaces based on key press
          switch(ev.key.keysym.sym) {
            case SDLK_UP:
              current_surface = key_press_surfaces[KEY_PRESS_SURFACE_UP];
              render_surface();
              break;

            case SDLK_DOWN:
              current_surface = key_press_surfaces[KEY_PRESS_SURFACE_DOWN];
              render_surface();
              break;

            case SDLK_LEFT:
              current_surface = key_press_surfaces[KEY_PRESS_SURFACE_LEFT];
              render_surface();
              break;

            case SDLK_RIGHT:
              current_surface = key_press_surfaces[KEY_PRESS_SURFACE_RIGHT];
              render_surface();
              break;

            case SDLK_p:
              current_surface = png_surface;
              render_surface();
              break;

            case SDLK_t:
              current_surface = png_surface;
              render_texture();
              break;

            case SDLK_g:
              render_geometry();
              break;

            case SDLK_v:
              render_viewport();
              break;

            default:
              current_surface = key_press_surfaces[KEY_PRESS_SURFACE_DEFAULT];
              break;
          }
          break;

        default:
          break;
      }
    }
  }
}

void render_surface() {
  // Apply the image
  SDL_BlitSurface(current_surface, NULL, screen_surface, NULL);

  // Update the surface
  SDL_UpdateWindowSurface(screen_window);
}

void render_texture() {
  // Show texture for 5 seconds
  // Clear screen
  SDL_RenderClear(screen_renderer);

  // Render texture to screen
  SDL_RenderCopy(screen_renderer, screen_texture, NULL, NULL);

  // Update screen
  SDL_RenderPresent(screen_renderer);

  SDL_Delay(5000);
}

void render_geometry() {
  SDL_Rect fill_rect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
  SDL_Rect outline_rect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };

  // Show geometry for 5 seconds
  // Clear screen
  SDL_RenderClear(screen_renderer);

  // Pick red color for renderer
  SDL_SetRenderDrawColor(screen_renderer, 0xFF, 0x00, 0x00, 0xFF);

  // Render rectangle
  SDL_RenderFillRect(screen_renderer, &fill_rect);

  // Pick green color for renderer
  SDL_SetRenderDrawColor(screen_renderer, 0x00, 0xFF, 0x00, 0xFF);

  // Draw react outline
  SDL_RenderDrawRect(screen_renderer, &outline_rect);

  // Pick blue color for renderer
  SDL_SetRenderDrawColor(screen_renderer, 0x00, 0x00, 0xFF, 0xFF);

  // Draw line
  SDL_RenderDrawLine(screen_renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

  // Pick yellow color for renderer
  SDL_SetRenderDrawColor(screen_renderer, 0xFF, 0xFF, 0x00, 0xFF);

  // Draw dotted line
  for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
    SDL_RenderDrawPoint(screen_renderer, SCREEN_WIDTH / 2, i);
  }

  // Update screen
  SDL_RenderPresent(screen_renderer);

  SDL_Delay(5000);

  // Reset renderer color to black
  SDL_SetRenderDrawColor(screen_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void render_viewport() {
  // Show viewport for 5 seconds

  // Top left corner viewport
  SDL_Rect top_left_viewport;
  top_left_viewport.x = 0;
  top_left_viewport.y = 0;
  top_left_viewport.w = SCREEN_WIDTH / 2;
  top_left_viewport.h = SCREEN_HEIGHT / 2;
  SDL_RenderSetViewport(screen_renderer, &top_left_viewport);

  // Render texture to screen
  SDL_RenderCopy(screen_renderer, screen_texture, NULL, NULL);

  // Top right viewport
  SDL_Rect top_right_viewport;
  top_right_viewport.x = SCREEN_WIDTH / 2;
  top_right_viewport.y = 0;
  top_right_viewport.w = SCREEN_WIDTH / 2;
  top_right_viewport.h = SCREEN_HEIGHT / 2;
  SDL_RenderSetViewport(screen_renderer, &top_right_viewport);

  // Render texture to screen
  SDL_RenderCopy(screen_renderer, screen_texture, NULL, NULL);

  // Bottom viewport
  SDL_Rect bottom_viewport;
  bottom_viewport.x = 0;
  bottom_viewport.y = SCREEN_HEIGHT / 2;
  bottom_viewport.w = SCREEN_WIDTH;
  bottom_viewport.h = SCREEN_HEIGHT / 2;
  SDL_RenderSetViewport(screen_renderer, &bottom_viewport );

  // Render texture to screen
  SDL_RenderCopy(screen_renderer, screen_texture, NULL, NULL);

  // Update screen
  SDL_RenderPresent(screen_renderer);

  SDL_Rect original_viewport;
  original_viewport.x = 0;
  original_viewport.y = 0;
  original_viewport.w = SCREEN_WIDTH;
  original_viewport.h = SCREEN_HEIGHT;

  SDL_RenderSetViewport(screen_renderer, &original_viewport);

  SDL_Delay(5000);
}