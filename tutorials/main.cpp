// 01_hello_SDL
// 02_getting_an_image_on_the_screen
// 03_event_driven_programming
// 04_key_presses
// 05_optimized_surface_loading_and_soft_stretching
// 06_loading_PNGs_with_SDL_image
// 07_texture_loading_and_rendering
// 08_geometry_rendering
// 09_the_viewport

#ifndef MAIN_H
#define MAIN_H
#include "main.hpp"
#endif

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture* screen_texture = NULL; // Window texture

SDL_Surface* key_press_surfaces[KEY_PRESS_SURFACE_TOTAL]; // Surfaces that correspond to a keypress
SDL_Surface* png_surface = NULL; // PNG surface
SDL_Surface* current_surface = NULL; // Selected surface

int main (int argc, char **args) {
  run();

  // Free resources and close SDL
  close();

  return 0;
}

void run() {
  std::unique_ptr<Store> store_p(new Store());

  // Start up SDL and create window
  if (!store_p->init()) {
    printf("Failed to initialize!\n");
  } else {
    if (store_p->load_media()) {
      // Apply the image stretched
      SDL_Rect stretch_rect;
      stretch_rect.x = 0;
      stretch_rect.y = 0;
      stretch_rect.w = SCREEN_WIDTH;
      stretch_rect.h = SCREEN_HEIGHT;
      SDL_Surface* stretched_surface = Surface::loadOptimized("resources/surfaces/stretch.bmp", store_p->window_surface_p);

      // Apply the image
      SDL_BlitScaled(stretched_surface, NULL, store_p->window_surface_p->pointer, &stretch_rect);

      // Update the surface
      SDL_UpdateWindowSurface(store_p->window_p->pointer);

      // Wait 2 seconds
      SDL_Delay(2000);

      Surface::free(stretched_surface);

      game_loop();
    } else {
      printf("Failed to load media\n");
    }
  }
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