#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct vec2 {
  public:
    float position_x;
    float position_y;
};

class player {
  public:
    const float *get_position_x() { return &position_.position_x; }
    const float *get_position_y() { return &position_.position_y; }
    void set_position_x(const float &x) { position_.position_x = x; }
    void set_position_y(const float &y) { position_.position_y = y; }

  private:
    vec2 position_;
};

class game {
  public:
    // value
    const int kheight = 400;
    const int kwidth = 600;

    void start() {
      init_window();
      main_loop();
    }

  private:
    // function
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

      // define background color
      glClearColor(0.5f, 0.0f, 1.0f, 0.0f);
    }

    void draw_player() {
    }

    /*
     * update elements for display
     */
    void update_status() {
      glClear(GL_COLOR_BUFFER_BIT);
      glfwSwapBuffers(window_);
    }

    void generate_output() {
      draw_player();
    }

    void main_loop()
    {
      while (!glfwWindowShouldClose(window_)) {
        if (glfwGetKey(window_, GLFW_KEY_ESCAPE)) break;
        glfwPollEvents();
        // process_input();
        update_status();
        generate_output();
      }
    }
    // value
    GLFWwindow *window_;
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
