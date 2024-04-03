#ifndef GLFW_PRAC_SRC_COLLIDING
#define GLFW_PRAC_SRC_COLLIDING

#include "circle.h"
#include "vector2.h"

class colliding {
  public:
    static bool is_colliding(const circle &a, const circle &b) {
      const float distance_x = a.get_center_x() - b.get_center_x();
      const float distance_y = a.get_center_y() - b.get_center_y();

      return ((a.get_radius() + b.get_radius()) * (a.get_radius() + b.get_radius())) >=
        (distance_x * distance_x + distance_y * distance_y);
    }

    static bool is_colliding(const float &radius_1, const float &center_x_1, const float &center_y_1,
        const float &radius_2, const float &center_x_2, const float &center_y_2) {
      const float distance_x = center_x_1 - center_x_2;
      const float distance_y = center_y_1 - center_y_2;

      return ((radius_1 + radius_2) * (radius_1 + radius_2)) >=
        (distance_x * distance_x + distance_y * distance_y);
    }

    static bool is_colliding(const float &radius_1, const vector2 &center_1,
        const float &radius_2, const vector2 &center_2) {
      const float distance_x = center_1.x - center_2.x;
      const float distance_y = center_1.y - center_2.y;

      return ((radius_1 + radius_2) * (radius_1 + radius_2)) >=
        (distance_x * distance_x + distance_y * distance_y);
    }
};

#endif
