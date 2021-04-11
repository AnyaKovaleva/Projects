#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const point_t& position, const double height, const double width);

  double getArea() const noexcept override;

  rectangle_t getFrameRect() const noexcept override;

  void move(const point_t& newPos) noexcept override;

  void move(double dx, double dy) noexcept override;

private:
  double height_;
  double width_;
  point_t position_;
};

#endif //A1_RECTANGLE_HPP
