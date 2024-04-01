#include "player_bullet.h"
#include <vector>

player_bullet::player_bullet(const float &position_x, const float &position_y)
{
  radius_ = (2.0f / 75.0f);
  position_.x = position_x;
  position_.y = position_y;
  circle_object_ = std::make_unique<circle>(position_.x, position_.y, radius_);
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
