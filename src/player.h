#ifndef GLFW_PRAC_PLAYER_H
#define GLFW_PRAC_PLAYER_H

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "object.h"
#include "vector2.h"
#include "y0_engine/object/VertexArray.h"

/*
 * for player object
 */
class player {
  public:
    player(GLint dimension,
           GLuint vertex_count,
           const GLfloat *vertices,
           GLuint index_count,
           const GLuint *indices,
           const GLfloat &kwidth_,
           const GLfloat &kheight_);
    virtual ~player();
    void draw();
    void draw(GLfloat *vertices);
    virtual void execute() const;

    const GLuint vertex_count_;
    const GLuint index_count_;
    vector2 position_;

    // private:
    std::shared_ptr<y0_engine::VertexArray> vertex_array_;
};

#endif
