// 01_hello_SDL
// 02_getting_an_image_on_the_screen
// 03_event_driven_programming
// 04_key_presses
// 05_optimized_surface_loading_and_soft_stretching
// 06_loading_PNGs_with_SDL_image
// 07_texture_loading_and_rendering
// 08_geometry_rendering
// 09_the_viewport
// 10_color_keying

#include "main.hpp"

int main(int argc, char **args) {
  if (init()) run(); else printf("Failed to initialize!\n");
  close();
  return 0;
}

bool init() {
  // Start SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
    return false;
  } else {
    // Create window
    return window_init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
  }
}

bool load_surface(int key, std::string resource_path) {
  return (surfaces[key] = surface_load_optimized(resource_path, global_window_p->surface_p)) != NULL;
}

bool load_texture(int key, std::string resource_path) {
  return (textures[key] = texture_load_from_file(resource_path, global_window_p->renderer_p))->loaded;
}

bool load_texture_color_keying(int key, std::string resource_path, int r, int g, int b) {
  return (textures[key] = texture_load_from_file(resource_path, global_window_p->renderer_p, true, r, g, b))->loaded;
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
  if (!load_texture(COMPOSITE_BACKGROUND_TEXTURE, "resources/textures/background.png")) return false;
  if (!load_texture_color_keying(COMPOSITE_PLAYER_TEXTURE, "resources/textures/player.png", 0, 0XFF, 0XFF)) return false;

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
    SDL_Surface* stretched_surface = surface_load_optimized("resources/surfaces/stretch.bmp", global_window_p->surface_p);

    // Apply the image
    SDL_BlitScaled(stretched_surface, NULL, global_window_p->surface_p, &stretch_rect);

    // Update the surface
    SDL_UpdateWindowSurface(global_window_p->p);

    // Wait 2 seconds
    SDL_Delay(2000);

    surface_free(stretched_surface);

    game_loop();
  } else {
    printf("Failed to load media\n");
  }
}

void close() {
  window_destroy();
  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void game_loop() {
  // Event object
  SDL_Event ev;

  // Set default surface
  window_render_surface(surfaces[KEY_PRESS_SURFACE_DEFAULT]);

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
            case SDLK_ESCAPE:
              return;
            case SDLK_UP:
              window_render_surface(surfaces[KEY_PRESS_SURFACE_UP]);
              break;

            case SDLK_DOWN:
              window_render_surface(surfaces[KEY_PRESS_SURFACE_DOWN]);
              break;

            case SDLK_LEFT:
              window_render_surface(surfaces[KEY_PRESS_SURFACE_LEFT]);
              break;

            case SDLK_RIGHT:
              window_render_surface(surfaces[KEY_PRESS_SURFACE_RIGHT]);
              break;

            case SDLK_p:
              window_render_surface(surfaces[KEY_PRESS_SURFACE_IMAGE]);
              break;

            case SDLK_g: {
              window_reset_renderer();

              // Render red filled quad
              SDL_Rect fill_rect = { WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_WIDTH / 2 };
              window_set_renderer_color(0xFF, 0x00, 0x00, 0xFF);
              window_add_geo_rect(&fill_rect);

              // Render green outlined quad
              SDL_Rect outline_rect = { WINDOW_WIDTH / 6, WINDOW_HEIGHT / 6, WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT * 2 / 3 };
              window_set_renderer_color(0x00, 0xFF, 0x00, 0xFF);
              window_add_geo_rect(&outline_rect);

              // Draw blue horizontal line
              window_set_renderer_color(0x00, 0x00, 0xFF, 0xFF);
              window_add_geo_line(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);

              // Draw vertical line of yellow dots
              window_set_renderer_color(0xFF, 0xFF, 0x00, 0xFF);
              for(int i = 0; i < WINDOW_HEIGHT; i += 4) window_add_geo_point(WINDOW_WIDTH / 2, i);

              window_render_renderer();
              break;
            }

            case SDLK_t: {
              window_reset_renderer();

              texture_t* texture_p = textures[VIEWPORT_TEXTURE];
              int old_width = texture_p->width;
              int old_height = texture_p->width;

              // Top Left
              texture_p->width = WINDOW_WIDTH / 2;
              texture_p->height = WINDOW_HEIGHT / 2;
              window_render_texture(texture_p, 0, 0);

              // Top Right
              window_render_texture(texture_p, WINDOW_WIDTH / 2, 0);

              // Bottom
              texture_p->width = WINDOW_WIDTH;
              texture_p->height = WINDOW_HEIGHT / 2;
              window_render_texture(texture_p, 0, WINDOW_HEIGHT / 2);

              texture_p->width = old_width;
              texture_p->height = old_height;

              window_render_renderer();
              break;
            }

            case SDLK_c: {
              window_reset_renderer();

              texture_t* player_texture_p = textures[COMPOSITE_PLAYER_TEXTURE];
              texture_t* background_texture_p = textures[COMPOSITE_BACKGROUND_TEXTURE];

              int old_background_width = background_texture_p->width;
              int old_background_height = background_texture_p->height;

              background_texture_p->width = WINDOW_WIDTH;
              background_texture_p->height = WINDOW_HEIGHT;
              window_render_texture(background_texture_p, 0, 0);
              window_render_texture(player_texture_p, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

              background_texture_p->width = old_background_width;
              background_texture_p->height = old_background_height;

              window_render_renderer();
              break;
            }

            default:
              window_render_surface(surfaces[KEY_PRESS_SURFACE_DEFAULT]);
              break;
          }
          break;

        default:
          break;
      }
    }
  }
}