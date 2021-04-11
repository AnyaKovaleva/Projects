#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

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

  return 0;
}
