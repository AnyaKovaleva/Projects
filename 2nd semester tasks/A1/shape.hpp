#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;

  virtual double getArea() const noexcept = 0;

  virtual rectangle_t getFrameRect() const noexcept = 0;

  virtual void move(const point_t& newPos) noexcept = 0;

  virtual void move(double dx, double dy) noexcept = 0;
  
};

#endif //A1_SHAPE_HPP
