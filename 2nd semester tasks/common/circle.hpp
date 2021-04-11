#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace kovaleva
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& position, const double radius);

    bool operator==(const Shape *other) noexcept override;

    bool operator!=(const Shape *other) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t& newPos) noexcept override;

    void move(double dx, double dy) noexcept override;

    void scale(double coefficient) override;

    void rotate(double angle) noexcept override;

    const char *getType() const override;

  private:
    double radius_;
    point_t position_;
    double rotation;
  };
}
#endif //A1_CIRCLE_HPP

