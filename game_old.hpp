#ifndef GAME_H
#define GAME_H

#ifndef CSTDIO_H
#define CSTDIO
#include <cstdio>
#endif

#include "mesh.hpp"
#include "shader.hpp"

#ifndef GLFW_H
#define GLFW_H
// Include all headers before this
#include <GLFW/glfw3.h>
#endif

class Game {
  public:
    Game(int width, int height, const char *title);
    ~Game();

    static void error_handler(int error, const char *description);
    static void key_handler(GLFWwindow* window, int key, int scancode, int action, int mods);

    int main_loop();
    void draw();

  private:
    GLFWwindow *window;
};
#endif