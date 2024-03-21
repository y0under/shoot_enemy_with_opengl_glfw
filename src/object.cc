#include "object.h"

object::object(GLint dimension, GLsizei vertexcount, const vertex *vertex)
{
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER,
      vertexcount * sizeof (vertex), vertex, GL_STATIC_DRAW);
  glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
}

object::~object()
{
  glDeleteVertexArrays(1, &vao_);
  glDeleteBuffers(1, &vbo_);
}

void object::bind() const
{
  glBindVertexArray(vao_);
}

