#include "player.h"

player::player(GLint dimension,
               GLuint vertex_count,
               const GLfloat *vertices,
               GLuint index_count,
               const GLuint *indices,
               const GLfloat &kwidth,
               const GLfloat &kheight)
  : vertex_array_(new y0_engine::VertexArray(dimension, vertices, vertex_count, indices, index_count)),
    vertex_count_(vertex_count),
    index_count_(index_count) {
  position_.x = 0;
  position_.y = -2.0f / kheight * 0.9f;
}

player::~player() {
}

void player::draw(GLfloat *vertices) {
  vertex_array_->bind(vertices);
  execute();
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);
}

void player::execute() const {
  // glDrawArrays(GL_LINE_LOOP, 0, vertex_count_);
  glDrawElements(GL_LINES, index_count_, GL_UNSIGNED_INT, 0);
}
