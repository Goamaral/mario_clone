#include "game.hpp"

int main() {
  Game game(640, 480, "HELLO");
  game.main_loop();
  
  return 0;
}