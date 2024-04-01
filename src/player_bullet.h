#ifndef GLFW_PRAC_SRC_PLAYER_BULLET_H
#define GLFW_PRAC_SRC_PLAYER_BULLET_H
#include <GL/glew.h>
#include <memory>
#include "circle.h"
#include "vector2.h"

class player_bullet {
  public:
    player_bullet(const float &position_x, const float &position_y);
    void draw() const;
    void shoot();
    // finish to move bullet
    void land();
    bool is_shoot();

  private:
    vector2 position_;
    float radius_;
    bool is_shoot_;
    std::unique_ptr<circle> circle_object_;
};

#endif
