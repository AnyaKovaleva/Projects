#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include "Shape.hpp"

void taskTwo(std::istream& in, std::ostream& out)
{
  std::vector<Shape> shapes{std::istream_iterator<Shape>(in), std::istream_iterator<Shape>()};

  if (!in.eof() && (in.fail() || in.bad()))
  {
    throw std::ios_base::failure("input error");
  }

  ShapeStats stats;
  std::for_each(shapes.begin(), shapes.end(), [&stats](const Shape& shape)
  {
    size_t vertices = shape.size();
    stats.verticesCount_ += vertices;
    if (checkTriangle(shape))
    {
      stats.trianglesCount_++;
    }
    else if (checkRectangle(shape))
    {
      if (checkSquare(shape))
      {
        stats.squaresCount_++;
        stats.rectanglesCount_++;
      }
      else
      {
        stats.rectanglesCount_++;
      }
    }
  });
  out << stats;

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), checkPentagon), shapes.end());

  out << "\nPoints: ";
  Shape points(shapes.size());

  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const Shape& shape)
  {
    return shape.front();
  });

  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));

  std::sort(shapes.begin(), shapes.end());

  out << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(std::cout, "\n"));
}
