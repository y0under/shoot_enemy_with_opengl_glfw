#ifndef Y0_SRC_SHADER_OPERATOR_H
#define Y0_SRC_SHADER_OPERATOR_H

#include <string>

#include <GLFW/glfw3.h>

/*
 * main task is loading shader and keeping program id
 */
class shader_operator {
  public:
    shader_operator();
    ~shader_operator();

    // load shader program for to get shader object id
    bool load_shader(const std::string &vertex_shader_file_name,
                     const std::string &fragment_shader_file_name);

    void set_target_shader();
    void unload_shader();

  private:
    bool compile_shader(const std::string &file_name,
                        GLenum shader_type,
                        GLuint &out_shader);
    // check the link between vertex shader and fragment shader
    bool is_valid_program();
    // check compile status
    bool is_success_compile(GLuint shader);
    // check link status
    bool is_valid_program(GLuint shader);


    GLuint vertex_shader_id_;
    GLuint fragment_shader_id_;
    GLuint shader_program_id_;
};

#endif
