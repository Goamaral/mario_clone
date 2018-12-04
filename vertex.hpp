#ifndef VERTEX_H
#define VERTEX_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#endif

class Vertex {
  public:
    Vertex(const glm::vec3 position);
  private:
    glm::vec3 position;
};
#endif