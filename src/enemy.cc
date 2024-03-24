#include "enemy.h"
#include <vector>

enemy::enemy(GLint dimension,
    GLsizei segments_count,
    const float radius,
    const float kheight,
    const float kwidth)
  : radius_(radius), segments_count_(segments_count)
{
  position_.x = 0;
  position_.y = 2.0f / kheight * 0.9f;
}

void enemy::draw() const
{
  glBegin(GL_TRIANGLE_FAN);
  std::vector<float> vertices;

  for (int i = 0; i < segments_count_; ++i) {
    float angle = 2.0f * M_PI * static_cast<float>(i) / static_cast<float>(segments_count_);
    float x = position_.x + radius_ * cos(angle);
    float y = position_.y + radius_ * sin(angle);
    vertices.push_back(x);
    vertices.push_back(y);
  }

  glVertexPointer(2, GL_FLOAT, 0, vertices.data());
  glEnableClientState(GL_VERTEX_ARRAY);

  execute();
  glEnd();
}

void enemy::execute() const
{
  glDrawArrays(GL_LINE_LOOP, 0, segments_count_);
}


