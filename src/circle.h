#ifndef GLFW_PRAC_SRC_CIRCLE_H
#define GLFW_PRAC_SRC_CIRCLE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <memory>

#include "y0_engine/object/VertexArray.h"

/*
 * to draw circle with opengl
 */
class circle {
  public:
    circle(const float &x, const float &y, const float &radius);
    // for normarized device coordinate
    circle(const float &x, const float &y, const float &radius,
           const uint32_t &width, const uint32_t &height);
    ~circle();
    void set_center(float x, float y);
    const float get_center_x() const;
    const float get_center_y() const;
    const float get_radius() const;
    void draw();

    static const int ksegments = 100;

  private:
    // for to indicate window shape
    enum {
      NORMAL,
      FAT,
      SLIM,
    };

    void update_vertices();

    float center_x_, center_y_;
    float radius_;
    float vertices_[2 * (ksegments + 2)];
    std::shared_ptr<y0_engine::VertexArray> object_;
    uint32_t window_shape_;
    float window_vertical_ratio_;
    float window_side_ratio_;
};

#endif
