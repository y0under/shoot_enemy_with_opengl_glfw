#include "circle.h"

circle::circle(float x, float y, float radius) {
  center_x_ = x;
  center_y_ = y;
  radius_ = radius;
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
    vertices_[2 * (i + 1)] = center_x_ + radius_ * cosf(theta);
    vertices_[2 * (i + 1) + 1] = center_y_ + radius_ * sinf(theta);
  }

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_DYNAMIC_DRAW);
}
