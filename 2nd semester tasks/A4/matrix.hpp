#ifndef KOVALEVA_ANNA_A4_MATRIX_HPP
#define KOVALEVA_ANNA_A4_MATRIX_HPP

#include <memory>
#include <iosfwd>
#include "shape.hpp"
#include "composite-shape.hpp"

namespace kovaleva
{
  class Matrix
  {
  public:

    Matrix() noexcept;

    Matrix(const Matrix& other);

    Matrix(Matrix&& other) noexcept;

    ~Matrix() = default;

    Matrix& operator=(const Matrix& other);

    Matrix& operator=(Matrix&& other) noexcept;

    std::unique_ptr<std::shared_ptr<Shape>[]> operator[](int index) const;

    void add(const std::shared_ptr<Shape>& shape);

    void add(const CompositeShape& compShape);

    unsigned int getNumberOfElementsInRow(int rowNum);

    void print(std::ostream& out);

  private:
    int rows_;
    int columns_;
    std::unique_ptr<std::shared_ptr<Shape>[]> matrix_;

    static bool isOverlap(const std::shared_ptr<Shape>& shape1, const std::shared_ptr<Shape>& shape2);
  };
}

#endif //KOVALEVA_ANNA_A4_MATRIX_HPP
