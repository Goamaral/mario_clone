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
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "SDL Tutorial"

int main (int argc, char **args) {
  run();

  // Free resources and close SDL
  close();

  return 0;
}

void run() {
  std::unique_ptr<Store> store_p(new Store());

  // Start up SDL and create window
  if (!store_p->init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)) {
    printf("Failed to initialize!\n");
  } else {
    if (store_p->load_media()) {
      // Apply the image stretched
      SDL_Rect stretch_rect;
      stretch_rect.x = 0;
      stretch_rect.y = 0;
      stretch_rect.w = WINDOW_WIDTH;
      stretch_rect.h = WINDOW_HEIGHT;
      SDL_Surface* stretched_surface = Surface::loadOptimized("resources/surfaces/stretch.bmp", store_p->window_p->surface_p);

      // Apply the image
      SDL_BlitScaled(stretched_surface, NULL, store_p->window_p->surface_p, &stretch_rect);


      // Update the surface
      SDL_UpdateWindowSurface(store_p->window_p->pointer);

      // Wait 2 seconds
      SDL_Delay(2000);

      Surface::free(stretched_surface);

      game_loop(store_p.get());
    } else {
      printf("Failed to load media\n");
    }
  }
}

void close() {
  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void game_loop(Store* store_p) {
  // Event object
  SDL_Event ev;

  // Set default surface
  store_p->window_p->render_surface(store_p->surfaces[KEY_PRESS_SURFACE_DEFAULT]);

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
              store_p->window_p->render_surface(store_p->surfaces[KEY_PRESS_SURFACE_UP]);
              break;

            case SDLK_DOWN:
              store_p->window_p->render_surface(store_p->surfaces[KEY_PRESS_SURFACE_DOWN]);
              break;

            case SDLK_LEFT:
              store_p->window_p->render_surface(store_p->surfaces[KEY_PRESS_SURFACE_LEFT]);
              break;

            case SDLK_RIGHT:
              store_p->window_p->render_surface(store_p->surfaces[KEY_PRESS_SURFACE_RIGHT]);
              break;

            case SDLK_p:
              store_p->window_p->render_surface(store_p->surfaces[KEY_PRESS_SURFACE_IMAGE]);
              break;

            case SDLK_t:
              store_p->window_p->render_surface(store_p->surfaces[KEY_PRESS_SURFACE_IMAGE]);
              break;

            case SDLK_g:
              //render_geometry();
              break;

            case SDLK_v:
              //render_viewport();
              break;

            default:
              store_p->window_p->render_surface(store_p->surfaces[KEY_PRESS_SURFACE_DEFAULT]);
              break;
          }
          break;

        default:
          break;
      }
    }
  }
}

/*

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
}*/