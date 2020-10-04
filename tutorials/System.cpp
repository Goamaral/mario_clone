#include "System.hpp"

System::System() {
  $sdl_inited = false;
  $sdl_img_inited = false;
}

System::~System() {
  $windows.clear();

  if ($sdl_img_inited) IMG_Quit();
  if ($sdl_inited) SDL_Quit();
}

void System::init(Uint32 flags) {
  SDL_assert(SDL_Init(flags) == 0);
  $sdl_inited = true;
}

void System::init_img_support(int flags) {
  SDL_assert((IMG_Init(flags) & flags) == flags);
  $sdl_img_inited = true;
}

std::shared_ptr<Window> System::create_window(std::string title, int width, int height) {
  std::shared_ptr<Window> window_p(new Window());

  window_p->init(title, width, height);
  $windows.push_back(window_p);

  return window_p;
}

void System::delay(Uint32 ms) {
  SDL_Delay(ms);
}

void System::event_loop(std::function<bool(SDL_Event)> event_handler) {
  SDL_Event event;
  bool running = true;

  while (running) {
    SDL_PollEvent(&event);
    running = event_handler(event);
  }
}