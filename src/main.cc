#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
 * out put result of compiling shader
 */
GLboolean printShaderInfoLog(GLuint shader, const char *str)
{
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;
  GLsizei bufSize;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);
  if (bufSize > 1)
  {
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }
  return static_cast<GLboolean>(status);
}

/*
 * out put linking result of program objedt
 */
GLboolean printProgramInfoLog(GLuint program)
{
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;
  GLsizei bufSize;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
  if (bufSize > 1)
  {
    std::vector<GLchar> infoLog(bufSize);
    GLsizei length;
    glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
    std::cerr << &infoLog[0] << std::endl;
  }
  return static_cast<GLboolean>(status);
}

GLuint crateShader()
{
  // vertex shader
  GLuint vShaderId = glCreateShader(GL_VERTEX_SHADER);
  std::string vertexShader = R"#(
#version 150 core
in vec4 position;
void main()
{
 gl_Position = position;
}
    )#";

  const char* vs = vertexShader.c_str();
  glShaderSource(vShaderId, 1, &vs, NULL);
  glCompileShader(vShaderId);

  // fragment shader
  GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  std::string fragmentShader = R"#(
#version 150 core
out vec4 fragment;
void main()
{
 fragment = vec4(1.0, 1.0, 1.0, 1.0);
}
    )#";
  const char* fs = fragmentShader.c_str();
  glShaderSource(fShaderId, 1, &fs, NULL);
  glCompileShader(fShaderId);

  GLuint programId = glCreateProgram();
  glAttachShader(programId,vShaderId);
  glAttachShader(programId,fShaderId);

  glLinkProgram(programId);

  glUseProgram(programId);

  return programId;
  }


class object {
  public:
    struct vertex
    {
      GLfloat position[2];
    };

    object(GLint dimension, GLsizei vertexcount, const vertex *vertex)
    {
      glGenVertexArrays(1, &vao_);
      glBindVertexArray(vao_);
      glGenBuffers(1, &vbo_);
      glBindBuffer(GL_ARRAY_BUFFER, vbo_);
      glBufferData(GL_ARRAY_BUFFER,
          vertexcount * sizeof (vertex), vertex, GL_STATIC_DRAW);
      glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(0);
    }

    virtual ~object()
    {
      glDeleteVertexArrays(1, &vao_);
      glDeleteBuffers(1, &vbo_);
    }

    void bind() const
    {
      glBindVertexArray(vao_);
    }

  private:
    // forbidden copy by copy constructor
    object(const object &o);
    // forbidden update by operator =
    object &operator=(const object &o);
    // vertex array object
    GLuint vao_;
    // vertex array object name
    GLuint vbo_;
};

/*
 * player object
 */
class player {
  public:
    player(GLint dimension, GLsizei vertex_count, const object::vertex *vertex)
      : object_(new object(dimension, vertex_count, vertex))
        , vertex_count_(vertex_count)
  {
  }

    void draw() const
    {
      object_->bind();
      execute();
    }

    virtual void execute() const
    {
      glDrawArrays(GL_LINE_LOOP, 0, vertex_count_);
    }

    const GLsizei vertex_count_;

  private:
    std::shared_ptr<const object> object_;
};

class game {
  public:
    const float kheight = 400;
    const float kwidth = 600;

    game() {
      player_verteces_[0] = { -0.05f, -0.95f };
      player_verteces_[1] = { 0.05f, -0.95f };
      player_verteces_[2] = { 0.05f, -0.9f };
      player_verteces_[3] = { -0.05f, -0.9f };
    } // player_(new player(kwidth, kheight)){}

void start() {
  init_window();
  player_ = std::move(std::make_unique<player>(2, 4, player_verteces_));
  program_id_ = crateShader();
  char c[256];
  printShaderInfoLog(program_id_, c);
  printProgramInfoLog(program_id_);
  main_loop();
}

private:
void init_window() {
  if (!glfwInit()) {
    throw std::runtime_error("GLFW is not initialized.");
  }

  // rgist process of ending
  atexit(glfwTerminate);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window(glfwCreateWindow(kwidth, kheight, "GLFW test", nullptr, nullptr));
  window_ = std::move(window);
  if (!window_) {
    throw std::runtime_error("Failed to create GLFW window.");
  }

  // let active window
  glfwMakeContextCurrent(window_);

  // init glew
  glewExperimental = GL_TRUE;

  if (glewInit() != GLEW_OK)
  {
    glfwDestroyWindow(window_);
    throw std::runtime_error("Can't initialize GLEW");
  }

}

void draw_player() {
  // draw model
  glDrawArrays(GL_LINE_LOOP, 0, player_->vertex_count_);
}

/*
 * update elements for display
 */
void update_status() {
}

void generate_output() {
  glUseProgram(program_id_);
  draw_player();
}

void main_loop()
{
  while (!glfwWindowShouldClose(window_)) {
    if (glfwGetKey(window_, GLFW_KEY_ESCAPE)) break;
    // define background color
    glClearColor(0.5f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);

    // process_input();
    update_status();
    generate_output();
    glfwSwapBuffers(window_);
    glfwPollEvents();
  }
}
// value
GLFWwindow *window_;
// std::unique_ptr<player> player_;
GLuint program_id_;
std::unique_ptr<player> player_;
object::vertex player_verteces_[4];
};

int main() {
  try{
    game game;
    game.start();
  }
  catch (std::exception(e)) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}
