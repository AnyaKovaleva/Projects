#ifndef KOVALEVA_ANNA_B5_SHAPE_HPP
#define KOVALEVA_ANNA_B5_SHAPE_HPP

#include <vector>
#include <iostream>

struct Point
{
  int x;
  int y;
};

struct ShapeStats
{
  ShapeStats();

  friend std::ostream& operator<<(std::ostream& out, const ShapeStats& stats);

  size_t verticesCount_;
  size_t trianglesCount_;
  size_t squaresCount_;
  size_t rectanglesCount_;
};

using Shape = std::vector<Point>;

std::istream& operator>>(std::istream& input, Point& point);

std::ostream& operator<<(std::ostream& out, const Point& point);

std::istream& operator>>(std::istream& input, Shape& shape);

std::ostream& operator<<(std::ostream& output, const Shape& shape);

bool operator<(const Shape& lhs, const Shape& rhs);

double getDistance(const Point& start, const Point& ending);

bool checkRectangle(const Shape& shape);

bool checkTriangle(const Shape& shape);

bool checkPentagon(const Shape& shape);

bool checkSquare(const Shape& shape);

#endif //KOVALEVA_ANNA_B5_SHAPE_HPP
