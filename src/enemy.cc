#include "enemy.h"
#include <vector>

enemy::enemy(const float &kheight, const float &kwidth)
{
  radius_ = (std::min(kwidth, kheight) * 0.1f);
  position_.x = 0;
  position_.y = 2.0f / kheight * 0.9f;
  circle_object_ = std::move(std::make_unique<circle>(position_.x, position_.y, radius_));
}

#include <iostream>

void enemy::draw() const
{
  circle_object_->draw();
}
