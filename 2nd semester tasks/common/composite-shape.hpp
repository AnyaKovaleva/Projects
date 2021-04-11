#ifndef KOVALEVA_ANNA_A3_COMPOSITE_SHAPE_HPP
#define KOVALEVA_ANNA_A3_COMPOSITE_SHAPE_HPP

#include "base-types.hpp"
#include "shape.hpp"

#include <memory>

namespace kovaleva
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();

    CompositeShape(const CompositeShape& other);

    CompositeShape(CompositeShape&& other) noexcept;

    ~CompositeShape() override = default;

    CompositeShape& operator=(const CompositeShape& other);

    CompositeShape& operator=(CompositeShape&& other) noexcept;

    std::shared_ptr<Shape> operator[](int index) const;

    bool operator==(const Shape *other) noexcept override;

    bool operator!=(const Shape *other) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const override;

    void move(const point_t& newPos) noexcept override;

    void move(double dx, double dy) noexcept override;

    void scale(double coefficient) override;

    void rotate(double angle) override;

    const char *getType() const override;

    void add(const std::shared_ptr<Shape>& newShape);

    void remove();

    int getSize() const noexcept;

  private:
    int size_;
    int capacity_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapes_;
  };

}

#endif //KOVALEVA_ANNA_A3_COMPOSITE_SHAPE_HPP
