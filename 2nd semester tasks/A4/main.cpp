#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "polygon.hpp"

using namespace kovaleva;

void testMoveFunction(Shape& figure)
{
  std::cout << "Move figure to (6, -4)\n";
  point_t newPos = {6, -4};
  figure.move(newPos);
  rectangle_t frameRect = figure.getFrameRect();
  std::cout << "figure's area: " << figure.getArea() << "\n";
  std::cout << "figure's frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

  std::cout << "Move figure 4, -26 \n";
  figure.move(4, -26);
  frameRect = figure.getFrameRect();
  std::cout << "figure's area: " << figure.getArea() << "\n";
  std::cout << "figure's frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

  std::cout << "Scale figure by 10 \n";
  figure.scale(10);
  frameRect = figure.getFrameRect();
  std::cout << "figure's area: " << figure.getArea() << "\n";
  std::cout << "figure's frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

  std::cout << "Rotate figure 45 degrees \n";
  figure.rotate(45);
  frameRect = figure.getFrameRect();
  std::cout << "figure's area: " << figure.getArea() << "\n";
  std::cout << "figure's frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

}

int main()
{
  point_t pos = {12, 3};
  try
  {
    Rectangle rect(pos, 4, 6);
    std::cout << "Test rectangle: \n";
    testMoveFunction(rect);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }

  try
  {
    Circle circle = {{20, -55}, 4};
    std::cout << "Test circle: \n";
    testMoveFunction(circle);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }

  try
  {
    kovaleva::point_t points[] = {
      {0, 3},
      {1, 4},
      {4, 4},
      {5, 3},
      {2, 0}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    std::cout << "Test Polygon: \n";
    testMoveFunction(polygon);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }

  CompositeShape compShapes;
  kovaleva::point_t points[] = {
    {0, 3},
    {1, 4},
    {4, 4},
    {5, 3},
    {2, 0}

  };
  Polygon polygon(sizeof(points) / sizeof(point_t), points);
  try
  {
    compShapes.add(std::make_shared<Circle>(point_t{12, 32}, 8));
    compShapes.add(std::make_shared<Rectangle>(point_t{43, 34}, 12, 20));
    compShapes.add(std::make_shared<Rectangle>(point_t{-43, -34}, 6, 2));
    compShapes.add(std::make_shared<Polygon>(polygon));
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }

  std::cout << "Testing composite shape:\n";
  std::cout << "compShapes size = " << compShapes.getSize() << ",  area = " << compShapes.getArea();
  rectangle_t frameRect = compShapes.getFrameRect();
  std::cout << ", frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

  std::cout << "Move compShapes to (2, -14)\n";
  point_t newPos = {2, -14};
  compShapes.move(newPos);
  frameRect = compShapes.getFrameRect();
  std::cout << "compShapes size = " << compShapes.getSize() << ",  area = " << compShapes.getArea()
    << ", frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

  std::cout << "Move compShapes 4, -26 \n";
  compShapes.move(4, -26);
  frameRect = compShapes.getFrameRect();
  std::cout << "compShapes size = " << compShapes.getSize() << ",  area = " << compShapes.getArea()
    << ", frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

  std::cout << "Scale compShapes by 10 \n";
  compShapes.scale(10);
  frameRect = compShapes.getFrameRect();
  std::cout << "compShapes size = " << compShapes.getSize() << ",  area = " << compShapes.getArea()
    << ", frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

  std::cout << "Rotate compShapes 90 degrees \n";
  compShapes.rotate(90);
  frameRect = compShapes.getFrameRect();
  std::cout << "compShapes size = " << compShapes.getSize() << ",  area = " << compShapes.getArea()
            << ", frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
            << frameRect.pos.y << " height: " << frameRect.height << " width: "
            << frameRect.width << "\n";

  Matrix m1;

  CompositeShape compShapes2;
  compShapes2.add(std::make_shared<Circle>(point_t{12, 2}, 3));
  compShapes2.add(std::make_shared<Rectangle>(point_t{-4, 5}, 4, 2));
  compShapes2.add(std::make_shared<Rectangle>(point_t{6, 2}, 2, 6));

  CompositeShape compShapes3;
  compShapes3.add(std::make_shared<Rectangle>(point_t{-4, 5}, 4, 2));
  compShapes3.add(std::make_shared<Rectangle>(point_t{6, 2}, 2, 6));
  compShapes3.add(std::make_shared<Circle>(point_t{12, 2}, 3));

  kovaleva::point_t polyPoints[] = {
    {12, -3},
    {14, 0},
    {16, 0},
    {18, -3},
    {16, -6},
    {14, -6},
  };
  Polygon polygon1(sizeof(polyPoints) / sizeof(point_t), polyPoints);
  try
  {
    m1.add(std::make_shared<Rectangle>(point_t{2, 2}, 2, 2));
    m1.add(std::make_shared<Rectangle>(point_t{3, -2}, 2, 4));
    m1.add(std::make_shared<Rectangle>(point_t{4, 5}, 2, 4));
    m1.add(std::make_shared<Circle>(point_t{10, 4}, 3));
    m1.add(std::make_shared<Rectangle>(point_t{5, 4}, 2, 2));
    m1.add(std::make_shared<Rectangle>(point_t{9, 0}, 4, 2));
    m1.add(std::make_shared<Circle>(point_t{10, 2}, 1));
    m1.add(std::make_shared<Rectangle>(point_t{0, 3}, 2, 4));
    m1.add(std::make_shared<Circle>(point_t{-3, -2}, 2));
    m1.add(compShapes2);
    m1.add(std::make_shared<Polygon>(polygon1));
    m1.add(std::make_shared<CompositeShape>(compShapes2));
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }

  m1.print(std::cout);

  return 0;
}
