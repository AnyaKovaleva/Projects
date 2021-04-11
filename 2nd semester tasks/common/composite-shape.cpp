#include "composite-shape.hpp"

#define _USE_MATH_DEFINES

#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <math.h>

kovaleva::CompositeShape::CompositeShape() :
  size_(0),
  capacity_(0),
  shapes_(nullptr)
{ }

kovaleva::CompositeShape::CompositeShape(const kovaleva::CompositeShape& other) :
  size_(other.size_),
  capacity_(other.capacity_),
  shapes_(std::make_unique<std::shared_ptr<Shape>[]>(capacity_))
{
  for (int i = 0; i < size_; ++i)
  {
    shapes_[i] = other.shapes_[i];
  }
}

kovaleva::CompositeShape::CompositeShape(kovaleva::CompositeShape&& other) noexcept:
  size_(other.size_),
  capacity_(other.capacity_),
  shapes_(std::move(other.shapes_))
{
  other.size_ = 0;
  other.capacity_ = 0;
  other.shapes_ = nullptr;
}

kovaleva::CompositeShape& kovaleva::CompositeShape::operator=(const kovaleva::CompositeShape& other)
{
  if (this != &other)
  {
    size_ = other.size_;
    capacity_ = other.capacity_;
    shapes_ = std::make_unique<std::shared_ptr<Shape>[]>(capacity_);

    for (int i = 0; i < size_; ++i)
    {
      shapes_[i] = other.shapes_[i];
    }
  }
  return *this;
}

kovaleva::CompositeShape& kovaleva::CompositeShape::operator=(kovaleva::CompositeShape&& other) noexcept
{
  if (this != &other)
  {
    size_ = other.size_;
    capacity_ = other.capacity_;
    shapes_ = std::move(other.shapes_);

    other.size_ = 0;
    other.capacity_ = 0;
    other.shapes_ = nullptr;
  }
  return *this;
}

std::shared_ptr<kovaleva::Shape> kovaleva::CompositeShape::operator[](int index) const
{
  if (size_ <= index || index < 0)
  {
    throw std::out_of_range("Index is out of range");
  }

  return shapes_[index];
}

double kovaleva::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < size_; i++)
  {
    area += shapes_[i]->getArea();
  }
  return area;
}

kovaleva::rectangle_t kovaleva::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  rectangle_t frameRect = shapes_[0]->getFrameRect();
  double minX = frameRect.pos.x - (frameRect.width / 2);
  double maxX = frameRect.pos.x + (frameRect.width / 2);
  double minY = frameRect.pos.y - (frameRect.height / 2);
  double maxY = frameRect.pos.y + (frameRect.height / 2);
  for (int i = 1; i < size_; i++)
  {
    frameRect = shapes_[i]->getFrameRect();
    minX = std::min(minX, frameRect.pos.x - (frameRect.width / 2));
    maxX = std::max(maxX, frameRect.pos.x + (frameRect.width / 2));
    minY = std::min(minY, frameRect.pos.y - (frameRect.height / 2));
    maxY = std::max(maxY, frameRect.pos.y + (frameRect.height / 2));
  }
  frameRect.width = maxX - minX;
  frameRect.height = maxY - minY;
  frameRect.pos = {(minX + frameRect.width / 2), (minY + frameRect.height / 2)};
  return frameRect;
}

void kovaleva::CompositeShape::move(const kovaleva::point_t& newPos) noexcept
{
  rectangle_t frameRect = getFrameRect();
  move(newPos.x - frameRect.pos.x, newPos.y - frameRect.pos.y);
}

void kovaleva::CompositeShape::move(double dx, double dy) noexcept
{
  for (int i = 0; i < size_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}

void kovaleva::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Error: coefficient can't be <=0");
  }
  for (int i = 0; i < size_; i++)
  {
    double dx = shapes_[i]->getFrameRect().pos.x - getFrameRect().pos.x;
    double dy = shapes_[i]->getFrameRect().pos.y - getFrameRect().pos.y;
    shapes_[i]->scale(coefficient);
    shapes_[i]->move(dx, dy);
  }
}

void kovaleva::CompositeShape::add(const std::shared_ptr<Shape>& newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Can't add new shape");
  }
  if (size_ == 0)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp(std::make_unique<std::shared_ptr<Shape>[]>(capacity_ + 1));
    capacity_++;
    size_++;
    temp[capacity_ - 1] = newShape;
    shapes_.swap(temp);
  }
  else if (capacity_ != size_)
  {
    size_++;
    shapes_[size_ - 1] = newShape;
  }
  else
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp(std::make_unique<std::shared_ptr<Shape>[]>(capacity_ * 2));
    capacity_ *= 2;
    for (int i = 0; i < size_; i++)
    {
      temp[i] = shapes_[i];
    }
    temp[size_] = newShape;
    size_++;
    shapes_.swap(temp);
  }
}

int kovaleva::CompositeShape::getSize() const noexcept
{
  return size_;
}

void kovaleva::CompositeShape::remove()
{
  if (size_ == 0)
  {
    throw std::underflow_error("Error: can't remove shape because CompositeShape is empty");
  }
  shapes_[--size_] = nullptr;

}

void kovaleva::CompositeShape::rotate(double angle)
{
  if (size_ == 0)
  {
    throw std::logic_error("Composite shape is empty");
  }
  point_t compShapesPos = getFrameRect().pos;
  double cosA = std::cos(angle * M_PI / 180);
  double sinA = std::sin(angle * M_PI / 180);
  for (int i = 0; i < size_; i++)
  {
    point_t shapePos = shapes_[i]->getFrameRect().pos;
    shapes_[i]->move({compShapesPos.x + cosA * (shapePos.x - compShapesPos.x) - sinA * (shapePos.y - compShapesPos.y),
                      compShapesPos.y + cosA * (shapePos.y - compShapesPos.y) + sinA * (shapePos.x - compShapesPos.x)});
    shapes_[i]->rotate(angle);
  }

}

const char *kovaleva::CompositeShape::getType() const
{
  return "CompositeShape";
}

bool kovaleva::CompositeShape::operator==(const kovaleva::Shape *other) noexcept
{
  if (other->getType() == getType())
  {
    const CompositeShape *otherCompShape = dynamic_cast<const CompositeShape *>(other);
    if (otherCompShape == nullptr)
    {
      return false;
    }
    if (size_ == otherCompShape->size_)
    {
      for (int i = 0; i < size_; i++)
      {
        if (this->shapes_[i].get() == otherCompShape->shapes_[i].get())
        {
          continue;
        }
        return false;
      }
      return true;
    }
  }
  return false;
}

bool kovaleva::CompositeShape::operator!=(const kovaleva::Shape *other) noexcept
{
  if (other->getType() == getType())
  {
    const CompositeShape *otherCompShape = dynamic_cast<const CompositeShape *>(other);
    if (otherCompShape == nullptr)
    {
      return false;
    }
    if (size_ == otherCompShape->size_)
    {
      for (int i = 0; i < size_; i++)
      {
        if (!(this->shapes_[i].get() == otherCompShape->shapes_[i].get()))
        {
          return true;
        }
      }
      return false;
    }
  }
  return true;
}








