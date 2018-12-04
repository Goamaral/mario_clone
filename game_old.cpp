#include "game.hpp"

// CONSTRUCTOR
Game::Game(int width, int height, const char *title) {
  if (!glfwInit()) {
    error_handler(0, "Failed to load GLFW");
    exit(0);
  }
 
  glfwSetErrorCallback(&Game::error_handler);

  if (!(window = glfwCreateWindow(width, height, title, NULL, NULL))) {
    error_handler(0, "Window or OpenGL context creation failed");
    exit(0);
  }

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, &Game::key_handler);

  glViewport(0, 0, width, height);
}

// DECONSTRUCTOR
Game::~Game() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

// STATIC
void Game::error_handler(int error, const char* description) {
  printf("Error(%d): %s\n", error, description);
}

void Game::key_handler(GLFWwindow* window, int key, int scancode, int action, int mods) {
  printf("key: %d action: %d\n", key, action);
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

// PUBLIC
int Game::main_loop() {
  printf("Creating shader\n");
  Shader shader("./shaders/basic");
  printf("Shader created\n");
  return 0;

  while(!glfwWindowShouldClose(window)) {
    // Clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw
    draw();

    // Render
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}

void Game::draw() {
  Vertex vertices[] = {
    Vertex(glm::vec3(-0.5, -0.5, 0)),
    Vertex(glm::vec3(0, 0.5, 0)),
    Vertex(glm::vec3(0.5, -0.5, 0))
  };

  Mesh mesh(vertices, sizeof(vertices) / sizeof(Vertex));

  mesh.draw();
}