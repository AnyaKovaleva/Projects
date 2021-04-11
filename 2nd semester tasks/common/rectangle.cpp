#include "rectangle.hpp"

#define _USE_MATH_DEFINES

#include <stdexcept>
#include <cmath>
#include <math.h>

kovaleva::Rectangle::Rectangle(const point_t& position, double height, double width) :
  height_(height),
  width_(width),
  position_(position),
  rotation_(0)
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

double kovaleva::Rectangle::getArea() const noexcept
{
  return (width_ * height_);
}

kovaleva::rectangle_t kovaleva::Rectangle::getFrameRect() const noexcept
{
  double width =
    width_ * std::abs(std::cos(rotation_ * M_PI / 180)) + height_ * std::abs(std::sin(rotation_ * M_PI / 180));
  double height =
    height_ * std::abs(std::cos(rotation_ * M_PI / 180)) + width_ * std::abs(std::sin(rotation_ * M_PI / 180));
  return rectangle_t{width, height, position_};
}

void kovaleva::Rectangle::move(const point_t& newPos) noexcept
{
  position_ = newPos;
}

void kovaleva::Rectangle::move(double dx, double dy) noexcept
{
  position_.x += dx;
  position_.y += dy;
}

void kovaleva::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Error: coefficient can't be <=0");
  }
  height_ *= coefficient;
  width_ *= coefficient;

}

void kovaleva::Rectangle::rotate(double angle) noexcept
{
  rotation_ += angle;
}

const char *kovaleva::Rectangle::getType() const
{
  return "Rectangle";
}

double kovaleva::Rectangle::getRotation()
{
  return rotation_;
}

bool kovaleva::Rectangle::operator==(const kovaleva::Shape *other) noexcept
{
  if (other->getType() == getType())
  {
    const Rectangle *otherRect = dynamic_cast<const Rectangle *>(other);
    if (otherRect == nullptr)
    {
      return false;
    }
    rectangle_t otherFrameRect = otherRect->getFrameRect();
    if ((position_.x == otherFrameRect.pos.x) &&
        (position_.y == otherFrameRect.pos.y))
    {
      if ((height_ == otherRect->height_) &&
          (width_ == otherRect->width_))
      {
        return true;
      }
    }
  }

  return false;
}

bool kovaleva::Rectangle::operator!=(const kovaleva::Shape *other) noexcept
{
  if (other->getType() == getType())
  {
    const Rectangle *otherRect = dynamic_cast<const Rectangle *>(other);
    if (otherRect == nullptr)
    {
      return false;
    }
    rectangle_t otherFrameRect = otherRect->getFrameRect();
    if ((position_.x == otherFrameRect.pos.x) &&
        (position_.y == otherFrameRect.pos.y))
    {
      if ((height_ == otherFrameRect.height) &&
          (width_ == otherFrameRect.width))
      {
        return false;
      }
    }
  }

  return true;
}




