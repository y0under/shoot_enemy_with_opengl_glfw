#ifndef GLFW_PRAC_SRC_CIRCLE_H
#define GLFW_PRAC_SRC_CIRCLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

/*
 * to draw circle with opengl
 */

class circle {
  public:
    circle(float x, float y, float radius_);
    ~circle();
    void set_center(float x, float y);
    const float get_center_x() const;
    const float get_center_y() const;
    const float get_radius() const;
    void draw();

    static const int ksegments = 100;

  private:

    void update_vertices();

    float center_x_, center_y_;
    float radius_;
    float vertices_[2 * (ksegments + 2)];
    GLuint vao_;
    GLuint vbo_;
};

#endif
