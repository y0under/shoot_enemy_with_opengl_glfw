#ifndef GLFW_PLAC_SRC_ENEMY_H
#define GLFW_PLAC_SRC_ENEMY_H

#include <GL/glew.h>
#include <memory>
#include "circle.h"
#include "vector2.h"

class enemy {
  public:
    enemy(const float &kheight, const float &kwidth);
    void draw() const;

  private:
    vector2 position_;
    float radius_;
    std::unique_ptr<circle> circle_object_;
};

#endif
