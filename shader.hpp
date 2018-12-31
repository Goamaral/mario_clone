#ifndef SHADER_H
#define SHADER_H

#ifndef GLEW_H
#define GLEW_H
#include <gl/glew.h>
#endif

#ifndef GL_H
#define GL_H
#include <SDL_opengl.h>
#endif

#ifndef STRING_H
#define STRING_H
#include <string>
#endif

#ifndef FSTREAM_H
#define FSTREAM_H
#include <fstream>
#endif

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif

class Shader {
  public:
    Shader(const std::string &file_name);
    ~Shader();

    void bind();

    static std::string load_shader(const std::string &file_name);
    static void check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string &error_message);
    static GLuint create_shader(const std::string &text, GLenum shader_type);

  private:
    static const unsigned int NUM_SHADERS = 2;

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};
#endif