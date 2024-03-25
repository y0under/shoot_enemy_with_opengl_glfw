#include "circle.h"

circle::circle(float x, float y) {
  center_x_ = x;
  center_y_ = y;
  update_vertices();
}

circle::~circle() {
  glDeleteBuffers(1, &vbo_);
}

void circle::draw() {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glDrawArrays(GL_TRIANGLE_FAN, 0, ksegments + 2);
}

void circle::set_center(float x, float y) {
  center_x_ = x;
  center_y_ = y;
  update_vertices();
}

void circle::update_vertices() {
  vertices_[0] = center_x_;
  vertices_[1] = center_y_;

  for (int i = 0; i <= ksegments; ++i) {
    float theta = 2.0f * M_PI * float(i) / float(ksegments); // 角度をラジアンに変換
    vertices_[2 * (i + 1)] = center_x_ + cosf(theta); // x座標
    vertices_[2 * (i + 1) + 1] = center_y_ + sinf(theta); // y座標
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);
}
