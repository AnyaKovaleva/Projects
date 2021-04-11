#include <iterator>
#include <cmath>
#include "Shape.hpp"
#include "usefulFunctions.hpp"

std::istream& operator>>(std::istream& input, Point& point)
{
  char openBracket = '\0';
  char closeBracket = '\0';
  char delimiter = '\0';

  int x = 0;
  int y = 0;

  input >> skipWsExceptNewLine >> std::noskipws >> openBracket
        >> skipWsExceptNewLine >> std::noskipws >> x
        >> skipWsExceptNewLine >> std::noskipws >> delimiter
        >> skipWsExceptNewLine >> std::noskipws >> y
        >> skipWsExceptNewLine >> std::noskipws >> closeBracket;

  if (delimiter != ';' || closeBracket != ')' || input.fail() || openBracket != '(')
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }

  point = {x, y};
  return input;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  return out << '(' << point.x << ';' << point.y << ')';
}

std::istream& operator>>(std::istream& input, Shape& shape)
{
  shape.clear();
  int vertices = 0;
  input >> std::ws >> vertices;

  if (input.eof() || input.fail() || vertices < 3)
  {
    input.setstate(std::ios_base::failbit);
    return input;
  }

  Point point{0, 0};
  for (int i = 0; i < vertices; i++)
  {
    input >> point;
    if (input.fail())
    {
      if (input.eof())
      {
        input.clear();
        input.setstate(std::ios_base::failbit);
      }
      return input;
    }
    shape.push_back(point);
  }
  input.clear();
  return input;
}

std::ostream& operator<<(std::ostream& output, const Shape& shape)
{
  output << shape.size() << " ";
  std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(output, " "));
  return output;
}

bool operator<(const Shape& lhs, const Shape& rhs)
{
  if (lhs.size() != rhs.size())
  {
    return lhs.size() < rhs.size();
  }

  if (checkRectangle(lhs) && checkRectangle(rhs))
  {
    if (checkSquare(lhs) && checkSquare(rhs))
    {
      return false;
    }
    return checkSquare(lhs) && !checkSquare(rhs);
  }
  return false;
}

double getDistance(const Point& first, const Point& second)
{
  double dx = first.x - second.x;
  double dy = first.y - second.y;
  return std::pow(dx, 2) + std::pow(dy, 2);
}

bool checkRectangle(const Shape& shape)
{
  if (shape.size() != 4)
  {
    return false;
  }

  double side_1 = getDistance(shape[0], shape[1]);
  double side_2 = getDistance(shape[1], shape[2]);
  double side_3 = getDistance(shape[2], shape[3]);
  double side_4 = getDistance(shape[3], shape[0]);
  double diagonal_1 = getDistance(shape[0], shape[2]);
  double diagonal_2 = getDistance(shape[1], shape[3]);

  return ((side_1 == side_3) && (side_2 == side_4) && (diagonal_1 == diagonal_2));

}

bool checkSquare(const Shape& shape)
{
  return checkRectangle(shape) && (getDistance(shape[0], shape[1]) == getDistance(shape[1], shape[2]));
}

bool checkTriangle(const Shape& shape)
{
  return shape.size() == 3;
}

bool checkPentagon(const Shape& shape)
{
  return shape.size() == 5;
}

ShapeStats::ShapeStats() :
  verticesCount_(0),
  trianglesCount_(0),
  squaresCount_(0),
  rectanglesCount_(0)
{ }

std::ostream& operator<<(std::ostream& out, const ShapeStats& stats)
{
  out << "Vertices: " << stats.verticesCount_ << "\n";
  out << "Triangles: " << stats.trianglesCount_ << "\n";
  out << "Squares: " << stats.squaresCount_ << "\n";
  out << "Rectangles: " << stats.rectanglesCount_ << "\n";
  return out;
}

