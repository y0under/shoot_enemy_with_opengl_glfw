#ifndef GLFW_PLAC_SRC_ENEMY_H
#define GLFW_PLAC_SRC_ENEMY_H

#include <GL/glew.h>
#include <memory>
#include "circle.h"
#include "vector2.h"

class enemy {
  public:
    enemy(const float &kheight, const float &kwidth);
    enemy(const float &kheight, const float &kwidth,
          const float position_x, const float position_y);
    void draw() const;
    const float get_radius() const;
    const vector2 get_center() const;
    bool is_alive();
    void kill();

  private:
    vector2 position_;
    float radius_;
    std::unique_ptr<circle> circle_object_;
    bool is_alive_;
};

#endif
