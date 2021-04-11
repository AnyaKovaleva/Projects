#include "matrix.hpp"
#include <stdexcept>
#include <ostream>
#include <cstring>

kovaleva::Matrix::Matrix() noexcept :
  rows_(0),
  columns_(0),
  matrix_()
{ }

kovaleva::Matrix::Matrix(const kovaleva::Matrix& other) :
  rows_(other.rows_),
  columns_(other.columns_),
  matrix_(std::make_unique<std::shared_ptr<Shape>[]>(other.rows_ * other.columns_))
{
  for (int i = 0; i < (rows_ * columns_); i++)
  {
    matrix_[i] = other.matrix_[i];
  }
}

kovaleva::Matrix::Matrix(kovaleva::Matrix&& other) noexcept :
  rows_(other.rows_),
  columns_(other.columns_),
  matrix_(std::move(other.matrix_))
{
  other.rows_ = 0;
  other.columns_ = 0;
}

kovaleva::Matrix& kovaleva::Matrix::operator=(const kovaleva::Matrix& other)
{
  if (this != &other)
  {
    rows_ = other.rows_;
    columns_ = other.columns_;
    std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix = std::make_unique<std::shared_ptr<Shape>[]>(rows_ * columns_);
    for (int i = 0; i < (rows_ * columns_); i++)
    {
      matrix_[i] = other.matrix_[i];
    }
  }
  return *this;
}

kovaleva::Matrix& kovaleva::Matrix::operator=(kovaleva::Matrix&& other) noexcept
{
  if (this != &other)
  {
    rows_ = other.rows_;
    columns_ = other.columns_;
    matrix_ = std::move(other.matrix_);
    other.rows_ = 0;
    other.columns_ = 0;
  }
  return *this;
}

std::unique_ptr<std::shared_ptr<kovaleva::Shape>[]> kovaleva::Matrix::operator[](int index) const
{
  if (index > rows_)
  {
    throw std::invalid_argument("Index is out of range");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix = std::make_unique<std::shared_ptr<Shape>[]>(columns_);
  for (int i = 0; i < columns_; i++)
  {
    if (matrix_[index * columns_ + i] != nullptr)
    {
      newMatrix[i] = matrix_[index * columns_ + i];
    }

  }
  return newMatrix;
}

void kovaleva::Matrix::add(const std::shared_ptr<Shape>& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape can't be nullptr");
  }

  if (matrix_ == nullptr)
  {

    matrix_ = std::make_unique<std::shared_ptr<Shape>[]>(1);
    matrix_[rows_ * columns_ + 0] = shape;
    columns_++;

    return;
  }
  int rowNum = 0;
  int columnNum = 0;
  bool overlap = false;
  bool rowFound = false;
  for (int i = 0; i <= rows_ && !rowFound; i++)
  {
    for (int j = 0; j < columns_ && !overlap; j++)
    {
      if (matrix_[i * columns_ + j] != nullptr)
      {
        if (shape == matrix_[i * columns_ + j])
        {
          throw std::invalid_argument("Shape already in matrix");
        }

        if (isOverlap(matrix_[i * columns_ + j], shape))
        {
          rowNum++;
          columnNum = 0;
          overlap = true;
          continue;
        }
        else
        {
          columnNum++;
        }
      }
    }

    if (!overlap)
    {
      rowFound = true;
    }
    else
    {
      overlap = false;
    }
  }

  int rows = rows_;
  int columns = columns_;
  if (rowNum > rows_)
  {
    rows_++;
  }
  if (columnNum + 1 > columns_)
  {
    columns_++;
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> newMatrix = std::make_unique<std::shared_ptr<Shape>[]>
    ((rows_ + 1) * columns_);

  for (int i = 0; i <= rows; i++)
  {
    for (int j = 0; j < columns; j++)
    {
      newMatrix[i * columns_ + j] = matrix_[i * columns + j];
    }
  }

  newMatrix[rowNum * columns_ + columnNum] = shape;
  matrix_.swap(newMatrix);
}

void kovaleva::Matrix::add(const kovaleva::CompositeShape& compShape)
{
  for (int i = 0; i < compShape.getSize(); i++)
  {
    add(compShape[i]);
  }
}

bool kovaleva::Matrix::isOverlap(const std::shared_ptr<Shape>& shape1, const std::shared_ptr<Shape>& shape2)
{
  rectangle_t frameRect1 = shape1->getFrameRect();
  rectangle_t frameRect2 = shape2->getFrameRect();

  point_t topLeft1 = {frameRect1.pos.x - frameRect1.width / 2, frameRect1.pos.y + frameRect1.height / 2};
  point_t bottomRight1 = {frameRect1.pos.x + frameRect1.width / 2, frameRect1.pos.y - frameRect1.height / 2};

  point_t topLeft2 = {frameRect2.pos.x - frameRect2.width / 2, frameRect2.pos.y + frameRect2.height / 2};
  point_t bottomRight2 = {frameRect2.pos.x + frameRect2.width / 2, frameRect2.pos.y - frameRect2.height / 2};

  return !((topLeft1.x >= bottomRight2.x || topLeft2.x >= bottomRight1.x) ||
           (topLeft1.y <= bottomRight2.y || topLeft2.y <= bottomRight1.y));

}

unsigned int kovaleva::Matrix::getNumberOfElementsInRow(int rowNum)
{
  if ((rowNum < 0) || (rowNum > rows_))
  {
    throw std::invalid_argument("Incorrect row number");
  }
  unsigned int numberOfElements = 0;
  for (int i = 0; i < columns_; i++)
  {
    if (matrix_[rowNum * columns_ + i] != nullptr)
    {
      numberOfElements++;
    }
  }

  return numberOfElements;
}

void kovaleva::Matrix::print(std::ostream& out)
{
  for (int i = 0; i <= rows_; i++)
  {
    for (int j = 0; j < columns_; j++)
    {
      if (matrix_[i * columns_ + j] != nullptr)
      {
        out << "[" << i << "][" << j << "] ";
        out << matrix_[i * columns_ + j]->getType() << " ";
        out << "pos x: " << matrix_[i * columns_ + j]->getFrameRect().pos.x << " y: "
            << matrix_[i * columns_ + j]->getFrameRect().pos.y;
        if (strcmp(matrix_[i * columns_ + j]->getType(), "Rectangle") == 0)
        {
          out << " height: " << matrix_[i * columns_ + j]->getFrameRect().height;
          out << " width: " << matrix_[i * columns_ + j]->getFrameRect().width << "\n";
        }
        else
        {
          if (strcmp(matrix_[i * columns_ + j]->getType(), "Circle") == 0)
          {
            out << " radius: " << matrix_[i * columns_ + j]->getFrameRect().width / 2 << "\n";
          }
        }
      }
    }
    out << "\n";
  }

}




