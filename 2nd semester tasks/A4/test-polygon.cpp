#include <memory>
#include <boost/test/unit_test.hpp>

#include "polygon.hpp"

using namespace kovaleva;

BOOST_AUTO_TEST_SUITE(TestPolygon, *boost::unit_test::tolerance(0.001))

  BOOST_AUTO_TEST_CASE(TestPolygonConstructorWithParameters)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };

    BOOST_CHECK_NO_THROW(Polygon polygon(sizeof(points) / sizeof(point_t), points));
  }

  BOOST_AUTO_TEST_CASE(PolygonLessVerticesTest)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 1}
    };

    BOOST_CHECK_THROW(Polygon polygon(sizeof(points) / sizeof(point_t), points), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(PolygonNotConvexTest)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 1},
      {1, 0},
      {0, 1}
    };

    BOOST_CHECK_THROW(Polygon polygon(sizeof(points) / sizeof(point_t), points), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonMoveTo)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    polygon.move({8.9, 2.5});
    rectangle_t frameRectAfterMove = polygon.getFrameRect();

    BOOST_TEST(frameRectAfterMove.pos.x, 8.9);
    BOOST_TEST(frameRectAfterMove.pos.y, 2.5);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonUnchangedFrameRectAfterMoveTo)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    rectangle_t frameRectBeforeMove = polygon.getFrameRect();

    polygon.move({8.9, 2.5});
    rectangle_t frameRectAfterMove = polygon.getFrameRect();

    BOOST_TEST(frameRectAfterMove.width, frameRectBeforeMove.width);
    BOOST_TEST(frameRectAfterMove.height, frameRectBeforeMove.height);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonUnchangedAreaAfterMoveTo)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    double areaBeforeMove = polygon.getArea();

    polygon.move({8.9, 2.5});
    double areaAfterMove = polygon.getArea();

    BOOST_TEST(areaBeforeMove, areaAfterMove);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonMoveBy)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    rectangle_t frameRectBeforeMove = polygon.getFrameRect();

    polygon.move(-2, 12);
    rectangle_t frameRectAfterMove = polygon.getFrameRect();

    BOOST_TEST(frameRectAfterMove.pos.x, frameRectBeforeMove.pos.x - 2);
    BOOST_TEST(frameRectAfterMove.pos.y, frameRectBeforeMove.pos.y + 12);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonUnchangedFrameRectAfterMoveBy)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    rectangle_t frameRectBeforeMove = polygon.getFrameRect();

    polygon.move(-2, 12);
    rectangle_t frameRectAfterMove = polygon.getFrameRect();

    BOOST_TEST(frameRectAfterMove.width, frameRectBeforeMove.width);
    BOOST_TEST(frameRectAfterMove.height, frameRectBeforeMove.height);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonUnchangedAreaAfterMoveBy)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    double areaBeforeMove = polygon.getArea();

    polygon.move(-2, 12);
    double areaAfterMove = polygon.getArea();

    BOOST_TEST(areaBeforeMove, areaAfterMove);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonScale)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    double areaBeforeScale = polygon.getArea();
    double coefficient = 15.0;

    polygon.scale(coefficient);
    double areaAfterScale = polygon.getArea();

    BOOST_TEST(areaAfterScale, areaBeforeScale * coefficient);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonScaleWithZeroCoefficient)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);

    BOOST_CHECK_THROW(polygon.scale(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestPolygonScaleWithNegativeCoefficient)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);

    BOOST_CHECK_THROW(polygon.scale(-10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(PolygonRotateTest)
  {
    kovaleva::point_t points[] = {
      {0, 0},
      {1, 0},
      {1, 1},
      {0, 1}
    };
    Polygon polygon(sizeof(points) / sizeof(point_t), points);
    rectangle_t frameRectBeforeRotate = polygon.getFrameRect();
    double areaBeforeRotate = polygon.getArea();

    polygon.rotate(45);
    rectangle_t frameRectAfterRotate = polygon.getFrameRect();
    double areaAfterRotate = polygon.getArea();

    BOOST_TEST(frameRectAfterRotate.pos.x, 0.5);
    BOOST_TEST(frameRectAfterRotate.pos.y, 0.5);
    BOOST_TEST(frameRectAfterRotate.width,
               frameRectBeforeRotate.width / std::sqrt(2) + frameRectBeforeRotate.height / std::sqrt(2));
    BOOST_TEST(frameRectAfterRotate.height,
               frameRectBeforeRotate.height / std::sqrt(2) + frameRectBeforeRotate.width / std::sqrt(2));
    BOOST_TEST(areaAfterRotate, areaBeforeRotate);
  }

BOOST_AUTO_TEST_SUITE_END()




