#include "colliding.h"

bool colliding::is_colliding(const circle &a, const circle &b) {
  const float distance_x = a.get_center_x() - b.get_center_x();
  const float distance_y = a.get_center_y() - b.get_center_y();

  return ((a.get_radius() + b.get_radius()) * (a.get_radius() + b.get_radius())) >=
         (distance_x * distance_x + distance_y * distance_y);
}
