#ifndef GLFW_PRAC_SRC_CIRCLE_H
#define GLFW_PRAC_SRC_CIRCLE_H

#include <GLFW/glfw3.h>
#include <cmath>


class circle {
  public:
    circle(float x, float y);
    ~circle();

    void set_center(float x, float y);

    void draw();

    static const int ksegments = 100; // 円を描画するためのセグメントの数

  private:

    void update_vertices();

    float center_x_, center_y_;
    float vertices_[2 * (ksegments + 2)];
    GLuint vbo_;
};

#endif
