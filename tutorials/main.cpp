// 01_hello_SDL
// 02_getting_an_image_on_the_screen
// 03_event_driven_programming
// 04_key_presses
// 05_optimized_surface_loading_and_soft_stretching
// 06_loading_PNGs_with_SDL_image
// 07_texture_loading_and_rendering
// 08_geometry_rendering
// 09_the_viewport

#include "main.hpp"

// Screen dimension constants
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WINDOW_TITLE "SDL Tutorial"

int main(int argc, char **args) {
  if (init()) run(); else printf("Failed to initialize!\n");
  close();
  return 0;
}

bool init() {
  // Start SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
  } else {
    // Create window
    window = Window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
  }

  return window.loaded;
}

bool load_surface(int key, std::string resource_path) {
  return surfaces[key] = Surface::loadOptimized(resource_path, window.surface_p);
}

bool load_texture(int key, std::string resource_path) {
  return textures[key] = Texture::load(resource_path, window.renderer_p);
}

bool load_media() {
  // Load surfaces
  if (!load_surface(KEY_PRESS_SURFACE_DEFAULT, "resources/surfaces/default.bmp")) return false;
  if (!load_surface(KEY_PRESS_SURFACE_UP, "resources/surfaces/up.bmp")) return false;
  if (!load_surface(KEY_PRESS_SURFACE_DOWN, "resources/surfaces/down.bmp")) return false;
  if (!load_surface(KEY_PRESS_SURFACE_LEFT, "resources/surfaces/left.bmp")) return false;
  if (!load_surface(KEY_PRESS_SURFACE_RIGHT, "resources/surfaces/right.bmp")) return false;
  if (!load_surface(KEY_PRESS_SURFACE_IMAGE, "resources/surfaces/image.png")) return false;

  // Load textures
  if (!load_texture(LOADING_TEXTURE, "resources/textures/texture.png")) return false;
  if (!load_texture(VIEWPORT_TEXTURE, "resources/textures/viewport.png")) return false;

  return true;
}

void run() {
  if (load_media()) {
    // Apply the image stretched
    SDL_Rect stretch_rect;
    stretch_rect.x = 0;
    stretch_rect.y = 0;
    stretch_rect.w = WINDOW_WIDTH;
    stretch_rect.h = WINDOW_HEIGHT;
    SDL_Surface* stretched_surface = Surface::loadOptimized("resources/surfaces/stretch.bmp", window.surface_p);

    // Apply the image
    SDL_BlitScaled(stretched_surface, NULL, window.surface_p, &stretch_rect);

    // Update the surface
    SDL_UpdateWindowSurface(window.p);

    // Wait 2 seconds
    SDL_Delay(2000);

    Surface::free(stretched_surface);

    game_loop();
  } else {
    printf("Failed to load media\n");
  }
}

void close() {
  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void game_loop() {
  // Event object
  SDL_Event ev;

  // Set default surface
  window.render_surface(surfaces[KEY_PRESS_SURFACE_DEFAULT]);

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
              window.render_surface(surfaces[KEY_PRESS_SURFACE_UP]);
              break;

            case SDLK_DOWN:
              window.render_surface(surfaces[KEY_PRESS_SURFACE_DOWN]);
              break;

            case SDLK_LEFT:
              window.render_surface(surfaces[KEY_PRESS_SURFACE_LEFT]);
              break;

            case SDLK_RIGHT:
              window.render_surface(surfaces[KEY_PRESS_SURFACE_RIGHT]);
              break;

            case SDLK_p:
              window.render_surface(surfaces[KEY_PRESS_SURFACE_IMAGE]);
              break;

            case SDLK_t:
              window.render_surface(surfaces[KEY_PRESS_SURFACE_IMAGE]);
              break;

            case SDLK_g:
              //render_geometry();
              break;

            case SDLK_v:
              // Top Left
              SDL_Rect top_left_viewport;
              top_left_viewport.x = 0;
              top_left_viewport.y = 0;
              top_left_viewport.w = WINDOW_WIDTH / 2;
              top_left_viewport.h = WINDOW_HEIGHT / 2;
              window.set_viewport(&top_left_viewport);
              window.render_texture(textures[VIEWPORT_TEXTURE]);

              // Top Right
              SDL_Rect top_right_viewport;
              top_right_viewport.x = WINDOW_WIDTH / 2;
              top_right_viewport.y = 0;
              top_right_viewport.w = WINDOW_WIDTH / 2;
              top_right_viewport.h = WINDOW_HEIGHT / 2;
              window.set_viewport(&top_right_viewport);
              window.render_texture(textures[VIEWPORT_TEXTURE]);

              // Bottom
              SDL_Rect bottom_viewport;
              bottom_viewport.x = 0;
              bottom_viewport.y = WINDOW_HEIGHT / 2;
              bottom_viewport.w = WINDOW_WIDTH;
              bottom_viewport.h = WINDOW_HEIGHT / 2;
              window.set_viewport(&bottom_viewport);
              window.render_texture(textures[VIEWPORT_TEXTURE]);

              window.render_viewports();
              break;

            default:
              window.render_surface(surfaces[KEY_PRESS_SURFACE_DEFAULT]);
              break;
          }
          break;

        default:
          break;
      }
    }
  }
}