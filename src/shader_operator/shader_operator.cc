#include "shader_operator.h"

#include <fstream>
#include <sstream>

bool is_success_compile(GLuint shader) {
  GLint compile_result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
  if (compile_result == GL_TRUE)
    return true;

  return false;
}

bool shader_operator::compile_shader(const std::string &file_name,
                                     GLenum shader_type,
                                     GLuint &out_shader) {
  std::ifstream shader_file(file_name);
  if (!shader_file.is_open())
    return false;

  // get stream buffer object
  std::stringstream sstream;
  sstream << shader_file.rdbuf();

  // get contents
  std::string s = sstream.str();
  const char *contents = s.c_str();

  out_shader = glCreateShader(shader_type);
  glShaderSource(out_shader, 1, &contents, nullptr);
  glCompileShader(out_shader);

  if (!is_success_compile(out_shader))
    return false;

  return true;
}

bool shader_operator::load_shader(const std::string &vertex_shader_file_name,
                                  const std::string &fragment_shader_file_name) {
  if (!compile_shader(vertex_shader_file_name, GL_VERTEX_SHADER, vertex_shader_id_) ||
      !compile_shader(fragment_shader_file_name, GL_FRAGMENT_SHADER, fragment_shader_id_))
    return false;

  shader_program_id_ = glCreateProgram();
  glAttachShader(shader_program_id_, vertex_shader_id_);
  glAttachShader(shader_program_id_, fragment_shader_id_);
  glLinkProgram(shader_program_id_);

  return true;
}
