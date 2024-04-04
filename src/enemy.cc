#include "enemy.h"
#include <vector>

enemy::enemy(const float &kheight, const float &kwidth) {
  is_alive_ = true;
  radius_ = (2.0f / 50.0f);
  position_.x = 0;
  position_.y = 0.5f;
  circle_object_ = std::move(std::make_unique<circle>(position_.x, position_.y, radius_,
                             kwidth, kheight));
}

enemy::enemy(const float &kheight, const float &kwidth,
             const float position_x, const float position_y) {
  radius_ = (2.0f / std::min(kwidth, kheight) * 50.0f);
  position_.x = position_x;
  position_.y = position_y;
  circle_object_ = std::move(std::make_unique<circle>(
                     position_.x, position_.y, radius_, kwidth, kheight));
}

void enemy::draw() const {
  if (!is_alive_) return;
  circle_object_->draw();
}

const vector2 enemy::get_center() const {
  return position_;
}

const float enemy::get_radius() const {
  return radius_;
}

bool enemy::is_alive() {
  return is_alive_;
}

void enemy::kill() {
  is_alive_ = false;
}
