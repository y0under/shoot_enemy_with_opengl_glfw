#include <iostream>
#include <stdexcept>
#include <GLFW/glfw3.h>

const int kheight = 400;
const int kwidth = 600;
GLFWwindow *window;

void init_window() {
  if (!glfwInit()) {
    throw std::runtime_error("GLFW is not initialized.");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(kwidth, kheight, "GLFW test", nullptr, nullptr);
}

void main_loop()
{
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

int main() {
  try{
  init_window();
  main_loop();
  }
  catch (std::exception(e)) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}
