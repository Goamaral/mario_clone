#include "shader.hpp"

// Contructor
Shader::Shader(const std::string &file_name) {
  printf("START\n");
  return;
  m_program = glCreateProgram();
  m_shaders[0] = create_shader(load_shader(file_name + ".vs"), GL_VERTEX_SHADER);
  m_shaders[1] = create_shader(load_shader(file_name + ".fs"), GL_FRAGMENT_SHADER);

  for(int i = 0; i < NUM_SHADERS; ++i) {
    glAttachShader(m_program, m_shaders[i]);
  }

  glBindAttribLocation(m_program, 0, "position");

  glLinkProgram(m_program);
  check_shader_error(m_program, GL_LINK_STATUS, true, "Error: Shader program linking failed: ");

  glValidateProgram(m_program);
  check_shader_error(m_program, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid: ");
  printf("END\n");
}

// Deconstructor
Shader::~Shader() {
  return;
  for(int i = 0; i < NUM_SHADERS; ++i) {
    glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }

  glDeleteProgram(m_program);
}

// Methods
void Shader::bind() {
  glUseProgram(m_program);
}

// Static
std::string Shader::load_shader(const std::string &file_name) {
  std::ifstream file;
  file.open(file_name.c_str());

  std::string output;
  std::string line;

  if(file.is_open()) {
    while(file.good()) {
      getline(file, line);
      output.append(line + "\n");
    }
  } else {
    std::cerr << "Unable to load shader: " << file_name << std::endl;
  }

  return output;
}

void Shader::check_shader_error(GLuint shader, GLuint flag, bool is_program, const std::string &error_message) {
  GLint success = 0;
  GLchar error[1024] = { 0 };

  if (is_program) {
    glGetProgramiv(shader, flag, &success);
  } else {
    glGetShaderiv(shader, flag, &success);
  }

  if (success == GL_FALSE) {
    if (is_program) {
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    } else {
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);
    }

    std::cerr << error_message << ": '" << error << "'" << std::endl;
  }
}

GLuint Shader::create_shader(const std::string &text, GLenum shader_type) {
  GLuint shader = glCreateShader(shader_type);

  if (shader == 0) {
    std::cerr << "Error: Shader creation failed!" << std::endl;
  }

  const GLchar* shader_source_strings[1];
  GLint shader_source_strings_lengths[1];

  shader_source_strings[0] = text.c_str();
  shader_source_strings_lengths[0] = text.length();

  glShaderSource(shader, 1, shader_source_strings, shader_source_strings_lengths);
  glCompileShader(shader);

  check_shader_error(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

  return shader;
}