#include "player_bullet.h"
#include <vector>

player_bullet::player_bullet()
{
  radius_ = (2.0f / 75.0f);
  circle_object_ = std::make_unique<circle>(0, 0, radius_);
}

void player_bullet::draw() const
{
  if (!is_shoot_) return;
  circle_object_->draw();
}

bool player_bullet::is_shoot() {
  return is_shoot_;
}

void player_bullet::shoot() {
  is_shoot_ = true;
}

void player_bullet::land() {
  is_shoot_ = false;
}

const vector2 player_bullet::get_center() const {
  vector2 v;
  v.x = circle_object_->get_center_x();
  v.y = circle_object_->get_center_y();
  return v;
}

void player_bullet::set_center(vector2 v) {
  circle_object_->set_center(v.x, v.y);
}
