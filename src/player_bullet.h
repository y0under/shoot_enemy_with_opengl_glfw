#ifndef GLFW_PRAC_SRC_PLAYER_BULLET_H
#define GLFW_PRAC_SRC_PLAYER_BULLET_H
#include <GL/glew.h>
#include <memory>

#include "circle.h"
#include "vector2.h"
#include "y0_engine/object/VertexArray.h"

class player_bullet {
  public:
    player_bullet(const float &kwindow_width, const float &kwindow_height);
    void draw() const;
    // start to move bullet
    void shoot();
    // finish to move bullet
    void land();
    bool is_shoot();
    const vector2 get_center() const;
    const float get_radius() const;
    void set_center(vector2 v);

  private:
    // vector2 position_;
    float radius_;
    bool is_shoot_;
    std::unique_ptr<circle> circle_object_;
};

#endif
