#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP

#include <string>
#include "base-types.hpp"

namespace kovaleva
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual bool operator==(const Shape *other) noexcept = 0;

    virtual bool operator!=(const Shape *other) noexcept = 0;

    virtual double getArea() const noexcept = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t& newPos) = 0;

    virtual void move(double dx, double dy) noexcept = 0;

    virtual void scale(double coefficient) = 0;

    virtual void rotate(double angle) = 0;

    virtual const char *getType() const = 0;

  };
}
#endif //A1_SHAPE_HPP
