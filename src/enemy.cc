#include "enemy.h"
#include <vector>

enemy::enemy(const float &kheight, const float &kwidth)
{
  radius_ = (2.0f / 50.0f);
  position_.x = 0;
  position_.y = 0.5f;
  circle_object_ = std::move(std::make_unique<circle>(position_.x, position_.y, radius_));
}

enemy::enemy(const float &kheight, const float &kwidth,
             const float position_x, const float position_y)
{
  radius_ = (2.0f / std::min(kwidth, kheight) * 50.0f);
  position_.x = position_x;
  position_.y = position_y;
  circle_object_ = std::move(std::make_unique<circle>(position_.x, position_.y, radius_));
}

#include <iostream>

void enemy::draw() const
{
  circle_object_->draw();
}
