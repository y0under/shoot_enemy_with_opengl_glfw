#ifndef GLFW_PLAC_SRC_ENEMY_H
#define GLFW_PLAC_SRC_ENEMY_H

#include <GL/glew.h>
#include <memory>
#include "vector2.h"

class enemy {
  public:
    enemy(GLint dimension,
        GLsizei vertex_count,
        const float radius,
        const float kheight,
        const float kwidth);
    void draw() const;
    virtual void execute() const;

    vector2 position_;

    const GLsizei segments_count_;
    const GLsizei radius_;
};

#endif
