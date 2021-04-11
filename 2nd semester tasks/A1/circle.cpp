#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t& position, double radius) :
  radius_(radius),
  position_(position)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Error: radius can't be <=0");
  }
}

double Circle::getArea() const noexcept
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return rectangle_t{radius_ * 2, radius_ * 2, position_};
}

void Circle::move(const point_t& newPos) noexcept
{
  position_ = newPos;
}

void Circle::move(double dx, double dy) noexcept
{
  position_.x += dx;
  position_.y += dy;
}




