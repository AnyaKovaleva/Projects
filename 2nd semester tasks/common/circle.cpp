#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>
#include <stdexcept>
#include <math.h>

kovaleva::Circle::Circle(const point_t& position, double radius) :
  radius_(radius),
  position_(position)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Error: radius can't be <=0");
  }
}

double kovaleva::Circle::getArea() const noexcept
{
  return radius_ * radius_ * M_PI;
}

kovaleva::rectangle_t kovaleva::Circle::getFrameRect() const noexcept
{
  return rectangle_t{radius_ * 2, radius_ * 2, position_};
}

void kovaleva::Circle::move(const point_t& newPos) noexcept
{
  position_ = newPos;
}

void kovaleva::Circle::move(double dx, double dy) noexcept
{
  position_.x += dx;
  position_.y += dy;
}

void kovaleva::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Error: coefficient can't be <=0");
  }
  radius_ *= coefficient;

}

void kovaleva::Circle::rotate(double angle) noexcept
{
  rotation = angle;

}

const char *kovaleva::Circle::getType() const
{
  return "Circle";
}

bool kovaleva::Circle::operator==(const kovaleva::Shape *other) noexcept
{
  if (other->getType() == getType())
  {
    const Circle *otherCircle = dynamic_cast<const Circle *>(other);
    if (otherCircle == nullptr)
    {
      return false;
    }
    rectangle_t otherFrameRect = otherCircle->getFrameRect();
    if ((position_.x == otherFrameRect.pos.x) &&
        (position_.y == otherFrameRect.pos.y))
    {
      if (radius_ == otherCircle->radius_)
      {
        return true;
      }
    }
  }
  return false;
}

bool kovaleva::Circle::operator!=(const kovaleva::Shape *other) noexcept
{
  if (other->getType() == getType())
  {
    const Circle *otherCircle = dynamic_cast<const Circle *>(other);
    if (otherCircle == nullptr)
    {
      return false;
    }
    rectangle_t otherFrameRect = otherCircle->getFrameRect();
    if ((position_.x == otherCircle->position_.x) &&
        (position_.y == otherFrameRect.pos.y))
    {
      if (radius_ == otherCircle->radius_)
      {
        return false;
      }
    }
  }
  return true;
}









