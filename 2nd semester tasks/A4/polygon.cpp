#include "polygon.hpp"

#define _USE_MATH_DEFINES

#include <algorithm>
#include <cmath>
#include <stdexcept>

kovaleva::Polygon::Polygon(int size, kovaleva::point_t *vertices) :
  size_(size)
{
  if (size <= 2)
  {
    throw std::invalid_argument("Polygon must have more than 2 vertices");
  }

  if (vertices == nullptr)
  {
    throw std::invalid_argument("Vertices can't be nullptr");
  }

  vertices_ = std::make_unique<kovaleva::point_t[]>(size_);
  for (int i = 0; i < size_; i++)
  {
    vertices_[i] = vertices[i];
  }

  bool isConvex = true;
  bool isNegative = false;
  for (int i = 0; i < size_; i++)
  {
    const point_t& vertex0 = vertices_[i];
    const point_t& vertex1 = vertices_[(i + 1) % size_];
    const point_t& vertex2 = vertices_[(i + 2) % size_];

    const point_t vertex01{vertex1.x - vertex0.x, vertex1.y - vertex0.y};
    const point_t vertex12{vertex2.x - vertex1.x, vertex2.y - vertex1.y};

    int cross = static_cast<int>(vertex01.x * vertex12.y - vertex01.y * vertex12.x);

    if (i == 0)
    {
      isNegative = cross < 0;
    }
    else
    {
      if ((cross < 0) != isNegative)
      {
        isConvex = false;
        break;
      }
    }
  }

  if (!isConvex)
  {
    throw std::invalid_argument("Polygon must be convex");
  }

}

kovaleva::Polygon::Polygon(const kovaleva::Polygon& other) :
  size_(other.size_),
  vertices_(std::make_unique<kovaleva::point_t[]>(size_))
{
  for (int i = 0; i < size_; i++)
  {
    vertices_[i] = other.vertices_[i];
  }
}

kovaleva::Polygon::Polygon(kovaleva::Polygon&& other) noexcept:
  size_(other.size_),
  vertices_(std::move(other.vertices_))
{
  if (this != &other)
  {
    other.size_ = 0;
    other.vertices_ = nullptr;
  }
}

kovaleva::Polygon& kovaleva::Polygon::operator=(const kovaleva::Polygon& other)
{
  if (this != &other)
  {
    size_ = other.size_;
    vertices_ = std::make_unique<kovaleva::point_t[]>(size_);
    for (int i = 0; i < size_; i++)
    {
      vertices_[i] = other.vertices_[i];
    }
  }
  return *this;
}

kovaleva::Polygon& kovaleva::Polygon::operator=(kovaleva::Polygon&& other) noexcept
{
  if (this != &other)
  {
    size_ = other.size_;
    other.size_ = 0;
    vertices_ = std::move(other.vertices_);
    other.vertices_ = nullptr;
  }
  return *this;
}

bool kovaleva::Polygon::operator==(const kovaleva::Shape *other) noexcept
{
  if (other->getType() == getType())
  {
    const Polygon *otherPolygon = dynamic_cast<const Polygon *>(other);
    if (otherPolygon == nullptr)
    {
      return false;
    }
    rectangle_t otherFrameRect = otherPolygon->getFrameRect();
    if ((getPosition().x == otherFrameRect.pos.x) &&
        (getPosition().y == otherFrameRect.pos.y))
    {
      if (size_ == otherPolygon->size_)
      {
        for (int i = 0; i < size_; i++)
        {
          if ((vertices_[i].x != otherPolygon->vertices_[i].x) || (vertices_[i].y != otherPolygon->vertices_[i].y))
          {
            return false;
          }
        }
        return true;
      }
    }
  }
  return false;
}

bool kovaleva::Polygon::operator!=(const kovaleva::Shape *other) noexcept
{
  if (other->getType() == getType())
  {
    const Polygon *otherPolygon = dynamic_cast<const Polygon *>(other);
    if (otherPolygon == nullptr)
    {
      return false;
    }
    rectangle_t otherFrameRect = otherPolygon->getFrameRect();
    if ((getPosition().x == otherFrameRect.pos.x) &&
        (getPosition().y == otherFrameRect.pos.y))
    {
      if (size_ == otherPolygon->size_)
      {
        for (int i = 0; i < size_; i++)
        {
          if ((vertices_[i].x != otherPolygon->vertices_[i].x) || (vertices_[i].y != otherPolygon->vertices_[i].y))
          {
            return true;
          }
        }
        return false;
      }
    }
  }
  return true;
}

double kovaleva::Polygon::getArea() const noexcept
{
  double area = 0;

  for (int i = 0; i < size_ - 1; i++)
  {
    area += vertices_[i].x * vertices_[i + 1].y;
    area -= vertices_[i + 1].x * vertices_[i].y;
  }

  area += vertices_[size_ - 1].x * vertices_[0].y;
  area -= vertices_[0].x * vertices_[size_ - 1].y;

  return std::fabs(area) / 2;

}

kovaleva::rectangle_t kovaleva::Polygon::getFrameRect() const noexcept
{
  double maxX = vertices_[0].x;
  double minX = vertices_[0].x;
  double maxY = vertices_[0].y;
  double minY = vertices_[0].y;

  for (int i = 0; i < size_; i++)
  {
    maxX = std::max(maxX, vertices_[i].x);
    minX = std::min(minX, vertices_[i].x);
    maxY = std::max(maxY, vertices_[i].y);
    minY = std::min(minY, vertices_[i].y);
  }

  const double width = (maxY - minY);
  const double height = (maxX - minX);
  const point_t posFrameRect = {minX + (width / 2), minY + (height / 2)};

  return rectangle_t{width, height, posFrameRect};
}

void kovaleva::Polygon::move(const kovaleva::point_t& newPos) noexcept
{
  point_t pos = getPosition();
  const double dx = newPos.x - pos.x;
  const double dy = newPos.y - pos.y;
  move(dx, dy);
}

void kovaleva::Polygon::move(double dx, double dy) noexcept
{
  for (int i = 0; i < size_; i++)
  {
    vertices_[i].x += dx;
    vertices_[i].y += dy;
  }
}

void kovaleva::Polygon::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Error: coefficient can't be <=0");
  }

  point_t pos = getPosition();
  for (int i = 0; i < size_; i++)
  {
    vertices_[i].x = pos.x + coefficient * (vertices_[i].x - pos.x);
    vertices_[i].y = pos.y + coefficient * (vertices_[i].y - pos.y);
  }
}

void kovaleva::Polygon::rotate(double angle) noexcept
{
  point_t pos = getPosition();
  double cosA = std::cos(angle * M_PI / 180);
  double sinA = std::sin(angle * M_PI / 180);

  for (int i = 0; i < size_; i++)
  {
    double dx = vertices_[i].x - pos.x;
    double dy = vertices_[i].y - pos.y;
    vertices_[i].x = pos.x + dx * cosA - dy * sinA;
    vertices_[i].y = pos.y + dx * sinA + dy * cosA;
  }

}

const char *kovaleva::Polygon::getType() const
{
  return "Polygon";
}

kovaleva::point_t kovaleva::Polygon::getPosition() const noexcept
{
  point_t pos = {0.0, 0.0};
  for (int i = 0; i < size_; i++)
  {
    pos.x += vertices_[i].x;
    pos.y += vertices_[i].y;
  }
  return {pos.x / size_, pos.y / size_};

}







