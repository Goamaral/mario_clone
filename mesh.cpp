#include "mesh.hpp"

// Constructor
Mesh::Mesh(Vertex *vertices, size_t vertices_length) {
  draw_count = vertices_length;
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);

  glGenBuffers(NUM_BUFFERS, vertex_array_buffers);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_array_buffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, vertices_length * sizeof(Vertex), &vertices, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
}

// Descontructor
Mesh::~Mesh() {
  glDeleteVertexArrays(1, &vertex_array_object);
}

// Methods
void Mesh::draw() {
  glBindVertexArray(vertex_array_object);

  glDrawArrays(GL_TRIANGLES, 0, draw_count);

  glBindVertexArray(0);
}