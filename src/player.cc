#include "player.h"

player::player(GLint dimension,
    GLsizei vertex_count,
    const object::vertex *vertex,
    const float kheight,
    const float kwidth)
  : object_(new object(dimension, vertex_count, vertex))
    , vertex_count_(vertex_count)
{
  position_.x = 0;
  position_.y = -2.0f / kheight * 0.9f;
}

void player::draw() const
{
  object_->bind();
  execute();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void player::execute() const
{
  glDrawArrays(GL_LINE_LOOP, 0, vertex_count_);
}
