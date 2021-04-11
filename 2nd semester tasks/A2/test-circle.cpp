#define _USE_MATH_DEFINES

#include <stdexcept>
#include <cmath>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"

using namespace kovaleva;

BOOST_AUTO_TEST_SUITE(TestCircle, *boost::unit_test::tolerance(0.001))

  BOOST_AUTO_TEST_CASE(TestCircleConstructor)
  {
    BOOST_CHECK_NO_THROW(Circle({{1, 5}, 4}));
  }

  BOOST_AUTO_TEST_CASE(TestCircleConstructorZeroRadius)
  {
    BOOST_CHECK_THROW(Circle({{1, 5}, 0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestCircleConstructorNegativeRadius)
  {
    BOOST_CHECK_THROW(Circle({{1, 5}, -4}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestCircleGetArea)
  {
    Circle circle({1, 5}, 4);
    double expectedArea = 4 * 4 * M_PI;
    double area = circle.getArea();
    BOOST_TEST(area == expectedArea);
  }

  BOOST_AUTO_TEST_CASE(TestCircleGetFrameRect)
  {
    Circle circle({1, 5}, 4);
    rectangle_t expectedFrameRect{8, 8, {1, 5}};
    rectangle_t frameRect = circle.getFrameRect();
    BOOST_TEST(frameRect.width == expectedFrameRect.width);
    BOOST_TEST(frameRect.height == expectedFrameRect.height);
    BOOST_TEST(frameRect.pos.x == expectedFrameRect.pos.x);
    BOOST_TEST(frameRect.pos.y == expectedFrameRect.pos.y);
  }

  BOOST_AUTO_TEST_CASE(TestCircleMoveToPosition)
  {
    Circle circle({1, 5}, 4);
    point_t newPosition = {2, 12};
    circle.move(newPosition);
    rectangle_t frameRectAfterMove = circle.getFrameRect();
    BOOST_TEST(frameRectAfterMove.pos.x == newPosition.x);
    BOOST_TEST(frameRectAfterMove.pos.y == newPosition.y);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedRadiusAfterCircleMoveToPosition)
  {
    Circle circle({1, 5}, 4);
    point_t newPosition = {2, 12};
    rectangle_t frameRectBeforeMove = circle.getFrameRect();
    double radiusBeforeMove = frameRectBeforeMove.width / 2;
    circle.move(newPosition);
    rectangle_t frameRectAfterMove = circle.getFrameRect();
    double radiusAfterMove = frameRectAfterMove.width / 2;
    BOOST_TEST(radiusAfterMove == radiusBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedCircleAreaAfterMoveToPosition)
  {
    Circle circle({1, 5}, 4);
    point_t newPosition = {2, 12};
    double areaBeforeMove = circle.getArea();
    circle.move(newPosition);
    double areaAfterMove = circle.getArea();
    BOOST_TEST(areaAfterMove == areaBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestCircleMoveBy)
  {
    Circle circle({1, 5}, 4);
    double dx = 10;
    double dy = -2;
    rectangle_t frameRectBeforeMove = circle.getFrameRect();
    circle.move(dx, dy);
    rectangle_t frameRectAfterMove = circle.getFrameRect();
    BOOST_TEST(frameRectAfterMove.pos.x == frameRectBeforeMove.pos.x + dx);
    BOOST_TEST(frameRectAfterMove.pos.y == frameRectBeforeMove.pos.y + dy);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedCircleRadiusAfterMoveToBy)
  {
    Circle circle({1, 5}, 4);
    double dx = 10;
    double dy = -2;
    rectangle_t frameRectBeforeMove = circle.getFrameRect();
    double radiusBeforeMove = frameRectBeforeMove.width / 2;
    circle.move(dx, dy);
    rectangle_t frameRectAfterMove = circle.getFrameRect();
    double radiusAfterMove = frameRectAfterMove.width / 2;
    BOOST_TEST(radiusAfterMove == radiusBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedCircleAreaAfterMoveBy)
  {
    Circle circle({1, 5}, 4);
    double dx = 10;
    double dy = -2;
    double areaBeforeMove = circle.getArea();
    circle.move(dx, dy);
    double areaAfterMove = circle.getArea();
    BOOST_TEST(areaAfterMove == areaBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestCircleScale)
  {
    Circle circle({1, 5}, 4);
    rectangle_t frameRectBeforeScale = circle.getFrameRect();
    double coefficient = 10;
    double expectedHeight = frameRectBeforeScale.height * coefficient;
    double expectedWidth = frameRectBeforeScale.width * coefficient;
    circle.scale(coefficient);
    rectangle_t frameRectAfterScale = circle.getFrameRect();
    BOOST_TEST(frameRectAfterScale.height == expectedHeight);
    BOOST_TEST(frameRectAfterScale.width == expectedWidth);
    BOOST_TEST(frameRectAfterScale.pos.x == frameRectBeforeScale.pos.x);
    BOOST_TEST(frameRectAfterScale.pos.y == frameRectBeforeScale.pos.y);
  }

  BOOST_AUTO_TEST_CASE(TestCircleAreaChangeAfterScale)
  {
    Circle circle({1, 5}, 4);
    double coefficient = 10;
    double areaBeforeScale = circle.getArea();
    circle.scale(coefficient);
    double areaAfterScale = circle.getArea();
    BOOST_TEST(areaAfterScale / areaBeforeScale == coefficient * coefficient);
  }

  BOOST_AUTO_TEST_CASE(TestCircleScaleWithZeroCoefficient)
  {
    Circle circle({1, 5}, 4);
    BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestCircleScaleWithNegativeCoefficient)
  {
    Circle circle({1, 5}, 4);
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

