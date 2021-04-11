#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace kovaleva
{

  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& position, const double height, const double width);

    bool operator==(const Shape *other) noexcept override;

    bool operator!=(const Shape *other) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t& newPos) noexcept override;

    void move(double dx, double dy) noexcept override;

    void scale(double coefficient) override;

    void rotate(double angle) noexcept override;

    const char *getType() const override;

    double getRotation();

  private:
    double height_;
    double width_;
    point_t position_;
    double rotation_;
  };
}

#endif //A1_RECTANGLE_HPP

