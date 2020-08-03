#include "14_animated_sprites_and_vsync.hpp"

int main(int argc, char** args) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize SDL_Error: %s\n", SDL_GetError());
    return 1;
  } else {
    event_loop();
    SDL_Quit();
    return 0;
  }
}

void event_loop() {
  Window window;
  window.init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT); // FUTURE: Write to STDERR if false returned

  Texture walking_texture;
  bool ok = walking_texture.load_from_file("resources/textures/walking.png", window.$sdl_renderer_p);
  if (!ok) return;

  const int WALKING_ANIMATION_FRAMES = 4;
  SDL_Rect walking_stripe_clips[WALKING_ANIMATION_FRAMES];

  // Walking Stripe Clip 0
  walking_stripe_clips[0].x = 0;
  walking_stripe_clips[0].y = 0;
  walking_stripe_clips[0].w = 64;
  walking_stripe_clips[0].h = 205;

  // Walking Stripe Clip 1
  walking_stripe_clips[1].x = 64;
  walking_stripe_clips[1].y = 0;
  walking_stripe_clips[1].w = 64;
  walking_stripe_clips[1].h = 205;

  // Walking Stripe Clip 2
  walking_stripe_clips[2].x = 128;
  walking_stripe_clips[2].y = 0;
  walking_stripe_clips[2].w = 64;
  walking_stripe_clips[2].h = 205;

  // Walking Stripe Clip 3
  walking_stripe_clips[3].x = 128;
  walking_stripe_clips[3].y = 0;
  walking_stripe_clips[3].w = 64;
  walking_stripe_clips[3].h = 205;

  int current_frame = 0;
  SDL_Event event;

  while (true) {
    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          return;

        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_ESCAPE:
              return;
          }
          break;

        default:
          printf("Unhandled event with type %d\n", event.type);
      }
    } else {
      window.clear_renderer();
      window.render_texture(&walking_texture, SDL_Rect(), walking_stripe_clips[current_frame]);
      window.apply_renderer();
      current_frame = (current_frame + 1) % WALKING_ANIMATION_FRAMES;
    }
  }
}