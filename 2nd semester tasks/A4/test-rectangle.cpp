#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "rectangle.hpp"

using namespace kovaleva;

BOOST_AUTO_TEST_SUITE(TestRectangle, *boost::unit_test::tolerance(0.001))

  BOOST_AUTO_TEST_CASE(TestRectangleConstructor)
  {
    BOOST_CHECK_NO_THROW(Rectangle({{1, 3}, 4, 8}));
  }

  BOOST_AUTO_TEST_CASE(TestRectangleConstructorZeroHeight)
  {
    BOOST_CHECK_THROW(Rectangle({{1, 3}, 0, 8}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleConstructorZeroWidth)
  {
    BOOST_CHECK_THROW(Rectangle({{1, 3}, 4, 0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleConstructorZeroHeightAndWidth)
  {
    BOOST_CHECK_THROW(Rectangle({{1, 3}, 0, 0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleConstructorNegativeHeight)
  {
    BOOST_CHECK_THROW(Rectangle({{1, 3}, -4, 8}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleConstructorNegativeWidth)
  {
    BOOST_CHECK_THROW(Rectangle({{1, 3}, 4, -8}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleGetArea)
  {
    Rectangle rect({1, 3}, 4, 5);
    double expectedArea = 20;
    double area = rect.getArea();
    BOOST_TEST(area == expectedArea);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleGetFrameRect)
  {
    Rectangle rect({1, 3}, 4, 5);
    rectangle_t expectedFrameRect{5, 4, {1, 3}};
    rectangle_t frameRect = rect.getFrameRect();
    BOOST_TEST(frameRect.width == expectedFrameRect.width);
    BOOST_TEST(frameRect.height == expectedFrameRect.height);
    BOOST_TEST(frameRect.pos.x == expectedFrameRect.pos.x);
    BOOST_TEST(frameRect.pos.y == expectedFrameRect.pos.y);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleMoveToPosition)
  {
    Rectangle rect({1, 3}, 4, 5);
    point_t newPosition = {2, 12};
    rect.move(newPosition);
    rectangle_t frameRectAfterMove = rect.getFrameRect();
    BOOST_TEST(frameRectAfterMove.pos.x == newPosition.x);
    BOOST_TEST(frameRectAfterMove.pos.y == newPosition.y);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedHeightAfterMoveToPosition)
  {
    Rectangle rect({1, 3}, 4, 5);
    point_t newPosition = {2, 12};
    rectangle_t frameRectBeforeMove = rect.getFrameRect();
    rect.move(newPosition);
    rectangle_t frameRectAfterMove = rect.getFrameRect();
    BOOST_TEST(frameRectAfterMove.height == frameRectBeforeMove.height);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedWidthAfterMoveToPosition)
  {
    Rectangle rect({1, 3}, 4, 5);
    point_t newPosition = {2, 12};
    rectangle_t frameRectBeforeMove = rect.getFrameRect();
    rect.move(newPosition);
    rectangle_t frameRectAfterMove = rect.getFrameRect();
    BOOST_TEST(frameRectAfterMove.width == frameRectBeforeMove.width);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedAreaAfterMoveToPosition)
  {
    Rectangle rect({1, 3}, 4, 5);
    point_t newPosition = {2, 12};
    double areaBeforeMove = rect.getArea();
    rect.move(newPosition);
    double areaAfterMove = rect.getArea();
    BOOST_TEST(areaAfterMove == areaBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleMoveBy)
  {
    Rectangle rect({1, 3}, 4, 5);
    double dx = 10;
    double dy = -2;
    rectangle_t frameRectBeforeMove = rect.getFrameRect();
    rect.move(dx, dy);
    rectangle_t frameRectAfterMove = rect.getFrameRect();
    BOOST_TEST(frameRectAfterMove.pos.x == frameRectBeforeMove.pos.x + dx);
    BOOST_TEST(frameRectAfterMove.pos.y == frameRectBeforeMove.pos.y + dy);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedHeightAfterMoveToBy)
  {
    Rectangle rect({1, 3}, 4, 5);
    double dx = 10;
    double dy = -2;
    rectangle_t frameRectBeforeMove = rect.getFrameRect();
    rect.move(dx, dy);
    rectangle_t frameRectAfterMove = rect.getFrameRect();
    BOOST_TEST(frameRectAfterMove.height == frameRectBeforeMove.height);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedWidthAfterMoveBy)
  {
    Rectangle rect({1, 3}, 4, 5);
    double dx = 10;
    double dy = -2;
    rectangle_t frameRectBeforeMove = rect.getFrameRect();
    rect.move(dx, dy);
    rectangle_t frameRectAfterMove = rect.getFrameRect();
    BOOST_TEST(frameRectAfterMove.width == frameRectBeforeMove.width);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedAreaAfterMoveBy)
  {
    Rectangle rect({1, 3}, 4, 5);
    double dx = 10;
    double dy = -2;
    double areaBeforeMove = rect.getArea();
    rect.move(dx, dy);
    double areaAfterMove = rect.getArea();
    BOOST_TEST(areaAfterMove == areaBeforeMove);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleScale)
  {
    Rectangle rect({1, 3}, 4, 5);
    rectangle_t frameRectBeforeScale = rect.getFrameRect();
    double coefficient = 10;
    double expectedHeight = frameRectBeforeScale.height * coefficient;
    double expectedWidth = frameRectBeforeScale.width * coefficient;
    rect.scale(coefficient);
    rectangle_t frameRectAfterScale = rect.getFrameRect();
    BOOST_TEST(frameRectAfterScale.height == expectedHeight);
    BOOST_TEST(frameRectAfterScale.width == expectedWidth);
    BOOST_TEST(frameRectAfterScale.pos.x == frameRectBeforeScale.pos.x);
    BOOST_TEST(frameRectAfterScale.pos.y == frameRectBeforeScale.pos.y);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleAreaChangeAfterScale)
  {
    Rectangle rect({1, 3}, 4, 5);
    double coefficient = 10;
    double expectedArea = rect.getArea() * coefficient * coefficient;
    rect.scale(coefficient);
    double areaAfterScale = rect.getArea();
    BOOST_TEST(areaAfterScale == expectedArea);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleScaleWithZeroCoefficient)
  {
    Rectangle rect({1, 3}, 4, 5);
    BOOST_CHECK_THROW(rect.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleScaleWithNegativeCoefficient)
  {
    Rectangle rect({1, 3}, 4, 5);
    BOOST_CHECK_THROW(rect.scale(-2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRectangleRotate)
  {
    Rectangle rect({1, 3}, 4, 5);
    rectangle_t frameRectBeforeRotation = rect.getFrameRect();
    double angle = 90;
    double expectedHeight = 5;
    double expectedWidth = 4;
    double areaBeforeRotate = rect.getArea();
    rect.rotate(angle);
    rectangle_t frameRectAfterRotation = rect.getFrameRect();
    BOOST_TEST(frameRectAfterRotation.pos.x == frameRectBeforeRotation.pos.x);
    BOOST_TEST(frameRectAfterRotation.pos.y == frameRectBeforeRotation.pos.y);
    BOOST_TEST(rect.getRotation() == angle);
    BOOST_TEST(frameRectAfterRotation.height == expectedHeight);
    BOOST_TEST(frameRectAfterRotation.width == expectedWidth);
    BOOST_TEST(rect.getArea() == areaBeforeRotate);
  }

BOOST_AUTO_TEST_SUITE_END()
