#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace kovaleva;

const double X1 = 8.4;
const double X2 = 9.1;
const double X3 = 26.2;

const double Y1 = 4.2;
const double Y2 = 2.6;
const double Y3 = 25;

const double WIDTH = 8;
const double HEIGHT = 12.4;
const double RADIUS = 3.4;

const double COEFFICIENT = 10.5;

BOOST_AUTO_TEST_SUITE(TestCompositeShape, *boost::unit_test::tolerance(0.001))

  BOOST_AUTO_TEST_CASE(TestCopyConstructor)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));

    CompositeShape otherCompositeShape(compositeShape);
    BOOST_TEST(compositeShape[0] == otherCompositeShape[0]);
    BOOST_TEST(compositeShape[1] == otherCompositeShape[1]);
    BOOST_TEST(compositeShape.getSize() == otherCompositeShape.getSize());
  }

  BOOST_AUTO_TEST_CASE(TestGetArea)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    double expectedArea = 0;
    for (int i = 0; i < compositeShape.getSize(); ++i)
    {
      expectedArea += compositeShape[i]->getArea();
    }

    BOOST_TEST(expectedArea, compositeShape.getArea());
  }

  BOOST_AUTO_TEST_CASE(TestGetFrameRect)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{3, 4}, 5));
    compositeShape.add(std::make_shared<Rectangle>(point_t{5.75, 4}, 10, 15.5));

    rectangle_t expectedFrameRect = {15.5, 10, {5.75, 4}};
    BOOST_TEST(expectedFrameRect.width, compositeShape.getFrameRect().width);
    BOOST_TEST(expectedFrameRect.height, compositeShape.getFrameRect().height);
    BOOST_TEST(expectedFrameRect.pos.x == compositeShape.getFrameRect().pos.x);
    BOOST_TEST(expectedFrameRect.pos.y == compositeShape.getFrameRect().pos.y);
  }

  BOOST_AUTO_TEST_CASE(TestMoveToPosition)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    BOOST_CHECK_NO_THROW(compositeShape.move({X3, Y3}));

    BOOST_TEST(compositeShape.getFrameRect().pos.x == X3);
    BOOST_TEST(compositeShape.getFrameRect().pos.y == Y3);
  }

  BOOST_AUTO_TEST_CASE(TestUnchhangedAreaAfterMoveToPosition)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    double areaBeforeMove = compositeShape.getArea();

    BOOST_CHECK_NO_THROW(compositeShape.move({X3, Y3}));

    BOOST_TEST(areaBeforeMove, compositeShape.getArea());
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedFrameRectAfterMoveToPosition)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    rectangle_t frameRectBeforeMove = compositeShape.getFrameRect();

    BOOST_CHECK_NO_THROW(compositeShape.move({X3, Y3}));

    BOOST_TEST(frameRectBeforeMove.width, compositeShape.getFrameRect().width);
    BOOST_TEST(frameRectBeforeMove.height, compositeShape.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(TestMoveBy)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    point_t positionOfCompositeShape = compositeShape.getFrameRect().pos;
    BOOST_CHECK_NO_THROW(compositeShape.move(X3, Y3));

    BOOST_TEST(compositeShape.getFrameRect().pos.x == positionOfCompositeShape.x + X3);
    BOOST_TEST(compositeShape.getFrameRect().pos.y == positionOfCompositeShape.y + Y3);
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedAreaAfterMoveBy)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    double areaBeforeMove = compositeShape.getArea();

    BOOST_CHECK_NO_THROW(compositeShape.move(X3, Y3));

    BOOST_TEST(areaBeforeMove, compositeShape.getArea());
  }

  BOOST_AUTO_TEST_CASE(TestUnchangedFrameRectAfterMoveBy)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    rectangle_t frameRectBeforeMove = compositeShape.getFrameRect();

    BOOST_CHECK_NO_THROW(compositeShape.move(X3, Y3));

    BOOST_TEST(frameRectBeforeMove.width, compositeShape.getFrameRect().width);
    BOOST_TEST(frameRectBeforeMove.height, compositeShape.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(TestScale)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    rectangle_t expectedFrameRect = {compositeShape.getFrameRect().width * COEFFICIENT,
                                     compositeShape.getFrameRect().height * COEFFICIENT,
                                     {compositeShape.getFrameRect().pos}};
    BOOST_CHECK_NO_THROW(compositeShape.scale(COEFFICIENT));
    BOOST_TEST(expectedFrameRect.width, compositeShape.getFrameRect().width);
    BOOST_TEST(expectedFrameRect.height, compositeShape.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithZeroCoefficient)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));

    BOOST_CHECK_THROW(compositeShape.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaleWithNegativeCoefficient)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));

    BOOST_CHECK_THROW(compositeShape.scale(-COEFFICIENT), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestAddShape)
  {
    CompositeShape compositeShape{};
    int sizeBeforeAddShape = compositeShape.getSize();
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));

    BOOST_TEST(sizeBeforeAddShape + 2 == compositeShape.getSize());
  }

  BOOST_AUTO_TEST_CASE(TestAddWithNullptr)
  {
    CompositeShape compositeShape{};

    BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestRemove)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));
    compositeShape.add(std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH));
    int sizeBeforeRemove = compositeShape.getSize();
    compositeShape.remove();

    BOOST_TEST(sizeBeforeRemove - 1 == compositeShape.getSize());
  }

  BOOST_AUTO_TEST_CASE(TestRemoveWithEmptyCompositeShape)
  {
    CompositeShape compositeShape{};

    BOOST_CHECK_THROW(compositeShape.remove(), std::underflow_error);
  }

  BOOST_AUTO_TEST_CASE(TestIndex)
  {
    CompositeShape compositeShape{};
    std::shared_ptr<Circle> circle = std::make_shared<Circle>(point_t{X1, Y1}, RADIUS);
    std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(point_t{X2, Y2}, HEIGHT, WIDTH);
    compositeShape.add(circle);
    compositeShape.add(rect);

    BOOST_TEST(compositeShape[0] == circle);
    BOOST_TEST(compositeShape[1] == rect);
  }

  BOOST_AUTO_TEST_CASE(TestOutOfRangeIndex)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{X1, Y1}, RADIUS));

    BOOST_CHECK_THROW(compositeShape[1], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(TestRotate)
  {
    CompositeShape compositeShape{};
    compositeShape.add(std::make_shared<Circle>(point_t{5, 15}, 4));
    compositeShape.add(std::make_shared<Rectangle>(point_t{6, 10}, 10, 20));
    rectangle_t frameRectBeforeRotation = compositeShape.getFrameRect();
    double angle = 90;
    double areaBeforeRotate = compositeShape.getArea();
    compositeShape.rotate(angle);
    rectangle_t frameRectAfterRotation = compositeShape.getFrameRect();
    BOOST_TEST(frameRectAfterRotation.pos.x == frameRectBeforeRotation.pos.x);
    BOOST_TEST(frameRectAfterRotation.pos.y == frameRectBeforeRotation.pos.y);
    BOOST_TEST(frameRectAfterRotation.height == frameRectBeforeRotation.width);
    BOOST_TEST(frameRectAfterRotation.width == frameRectBeforeRotation.height);
    BOOST_TEST(compositeShape.getArea() == areaBeforeRotate);
  }

BOOST_AUTO_TEST_SUITE_END()


