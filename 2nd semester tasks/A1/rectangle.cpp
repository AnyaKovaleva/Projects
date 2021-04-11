#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t& position, double height, double width) :
  height_(height),
  width_(width),
  position_(position)
{
  if (height_ <= 0)
  {
    throw std::invalid_argument("Error: height can't be <=0");
  }
  if (width_ <= 0)
  {
    throw std::invalid_argument("Error: width can't be <=0");
  }
}

double Rectangle::getArea() const noexcept
{
  return (width_ * height_);
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return rectangle_t{width_, height_, position_};
}

void Rectangle::move(const point_t& newPos) noexcept
{
  position_ = newPos;
}

void Rectangle::move(double dx, double dy) noexcept
{
  position_.x += dx;
  position_.y += dy;
}
