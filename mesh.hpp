#ifndef MESH_H
#define MESH_H

#ifndef GLEW_H
#define GLEW_H
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include "vertex.hpp"

class Mesh {
  public:
    Mesh(Vertex *vertices, size_t vertices_length);
    ~Mesh();

    void draw();

  private:
    enum { POSITION_VB, NUM_BUFFERS };
    GLuint vertex_array_object;
    GLuint vertex_array_buffers[NUM_BUFFERS];
    unsigned int draw_count;
};
#endif