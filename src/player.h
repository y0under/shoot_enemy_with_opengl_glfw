#ifndef GLFW_PRAC_PLAYER_H
#define GLFW_PRAC_PLAYER_H

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "object.h"
#include "vector2.h"

/*
 * for player object
 */
class player {
  public:
    player(GLint dimension,
        GLsizei vertex_count,
        const object::vertex *vertex,
        const float kheight,
        const float kwidth);
    void draw() const;
    virtual void execute() const;

    const GLsizei vertex_count_;
    vector2 position_;

    // private:
    std::shared_ptr<const object> object_;
};

#endif
