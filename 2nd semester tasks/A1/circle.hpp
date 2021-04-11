#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t& position, const double radius);

  double getArea() const noexcept override;

  rectangle_t getFrameRect() const noexcept override;

  void move(const point_t& newPos) noexcept override;

  void move(double dx, double dy) noexcept override;

private:
  double radius_;
  point_t position_;
};

#endif //A1_CIRCLE_HPP
