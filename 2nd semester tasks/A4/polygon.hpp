#ifndef KOVALEVA_ANNA_A4_POLYGON_HPP
#define KOVALEVA_ANNA_A4_POLYGON_HPP

#include <memory>
#include "shape.hpp"

namespace kovaleva
{
  class Polygon : public Shape
  {
  public:

    Polygon(int size, point_t *vertices);

    Polygon(const Polygon& other);

    Polygon(Polygon&& other) noexcept;

    ~Polygon() override = default;

    Polygon& operator=(const Polygon& other);

    Polygon& operator=(Polygon&& other) noexcept;

    bool operator==(const Shape *other) noexcept override;

    bool operator!=(const Shape *other) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t& newPos) noexcept override;

    void move(double dx, double dy) noexcept override;

    void scale(double coefficient) override;

    void rotate(double angle) noexcept override;

    const char *getType() const override;

    point_t getPosition() const noexcept;

  private:
    int size_;
    std::unique_ptr<point_t[]> vertices_;
  };
}

#endif //KOVALEVA_ANNA_A4_POLYGON_HPP
