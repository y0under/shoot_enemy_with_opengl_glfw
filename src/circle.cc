#include "circle.h"

#include <iostream>

circle::circle(const float &x, const float &y, const float &radius) {
  center_x_ = x;
  center_y_ = y;
  radius_ = radius;

  window_shape_ = NORMAL;
  window_vertical_ratio_ = 1.0f;
  window_side_ratio_ = 1.0f;

  update_vertices();

  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
}

circle::circle(const float &x, const float &y, const float &radius,
               const uint32_t &width, const uint32_t &height) {
  center_x_ = x;
  center_y_ = y;
  radius_ = radius;

  window_shape_ = (width == height ? NORMAL : (width < height ? SLIM : FAT));
  float window_ratio = std::fmin(width, height) / std::fmax(width, height);
  window_vertical_ratio_ = width < height ? window_ratio : 1.0f;
  window_side_ratio_ = height < width ? window_ratio : 1.0f;

  update_vertices();

  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
}

circle::~circle() {
  glDeleteBuffers(1, &vbo_);
}

void circle::draw() {
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  // glDrawArrays(GL_LINE_LOOP, 0, ksegments + 2);
  glDrawArrays(GL_TRIANGLE_FAN, 0, ksegments + 2);

  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void circle::set_center(float x, float y) {
  center_x_ = x;
  center_y_ = y;
  update_vertices();
}

const float circle::get_center_x() const {
  return center_x_;
}

const float circle::get_center_y() const {
  return center_y_;
}

const float circle::get_radius() const {
  return radius_;
}

void circle::update_vertices() {
  vertices_[0] = center_x_;
  vertices_[1] = center_y_;

  for (int i = 0; i <= ksegments; ++i) {
    float theta = 2.0f * M_PI * float(i) / float(ksegments);
    vertices_[2 * (i + 1)] = center_x_ + radius_ * cosf(theta) * window_side_ratio_;
    vertices_[2 * (i + 1) + 1] = center_y_ + radius_ * sinf(theta) * window_vertical_ratio_;
  }

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_DYNAMIC_DRAW);
}
