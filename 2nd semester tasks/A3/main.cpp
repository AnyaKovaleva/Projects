#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

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

  CompositeShape compShapes;
  Circle circle1 = {{12, 32}, 8};
  Rectangle rect1 = {{43, 34}, 12, 20};
  Rectangle rect2 = {{-43, -34}, 6, 2};
  try
  {
    compShapes.add(std::make_shared<Circle>(circle1));
    compShapes.add(std::make_shared<Rectangle>(rect1));
    compShapes.add(std::make_shared<Rectangle>(rect2));
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "Error!" << "\n";
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
  std::cout << "figure's area: " << compShapes.getArea() << "\n";
  std::cout << "compShapes size = " << compShapes.getSize() << ",  area = " << compShapes.getArea()
    << ", frame rectangle:\nposition: x: " << frameRect.pos.x << " y: "
    << frameRect.pos.y << " height: " << frameRect.height << " width: "
    << frameRect.width << "\n";

  return 0;
}

