#include <memory>
#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include "matrix.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace kovaleva;

BOOST_AUTO_TEST_SUITE(TestMatrix, *boost::unit_test::tolerance(0.001))

  BOOST_AUTO_TEST_CASE(TestMatrixConstructor)
  {
    BOOST_CHECK_NO_THROW(Matrix matrix);
  }

  BOOST_AUTO_TEST_CASE(TestMatrixAdd)
  {
    Rectangle rect1 = {{2, 2}, 2, 2};
    Rectangle rect2 = {{3, -2}, 2, 4};
    Circle circle = {{2, -2}, 3};

    Matrix matrix;

    BOOST_CHECK_NO_THROW(matrix.add(std::make_shared<Rectangle>(rect1)));
    BOOST_CHECK_NO_THROW(matrix.add(std::make_shared<Rectangle>(rect2)));
    BOOST_CHECK_NO_THROW(matrix.add(std::make_shared<Circle>(circle)));
  }

  BOOST_AUTO_TEST_CASE(TestMatrixAddCompositeShape)
  {
    Circle circle = {{12, 2}, 3};
    Rectangle rect1 = {{-4, 5}, 4, 2};
    Rectangle rect2 = {{6, 2}, 2, 8};

    CompositeShape compShapes;
    compShapes.add(std::make_shared<Circle>(circle));
    compShapes.add(std::make_shared<Rectangle>(rect1));
    compShapes.add(std::make_shared<Rectangle>(rect2));

    Matrix matrix;
    BOOST_CHECK_NO_THROW(matrix.add(compShapes));
  }

  BOOST_AUTO_TEST_CASE(TestMatrixAddCompositeShapeAsOneObject)
  {
    Circle circle = {{12, 2}, 3};
    Rectangle rect1 = {{-4, 5}, 4, 2};
    Rectangle rect2 = {{6, 2}, 2, 8};

    CompositeShape compShapes;
    compShapes.add(std::make_shared<Circle>(circle));
    compShapes.add(std::make_shared<Rectangle>(rect1));
    compShapes.add(std::make_shared<Rectangle>(rect2));

    Matrix matrix;
    BOOST_CHECK_NO_THROW(matrix.add(std::make_shared<CompositeShape>(compShapes)));
  }

  BOOST_AUTO_TEST_CASE(TestMatrixAddExistingShape)
  {
    Rectangle rect1 = {{2, 2}, 2, 2};
    Rectangle rect2 = {{3, -2}, 2, 4};
    Circle circle = {{2, -2}, 3};

    Matrix matrix;
    matrix.add(std::make_shared<Rectangle>(rect1));
    matrix.add(std::make_shared<Rectangle>(rect2));
    matrix.add(std::make_shared<Circle>(circle));

    BOOST_CHECK_THROW(matrix.add(matrix[0][1]), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMatrixAddExistingCompositeShapeAsOneObject)
  {
    Rectangle rect1 = {{2, 2}, 2, 2};
    Rectangle rect2 = {{3, -2}, 2, 4};
    Circle circle = {{2, -2}, 3};

    CompositeShape compShapes;
    compShapes.add(std::make_shared<Circle>(circle));
    compShapes.add(std::make_shared<Rectangle>(rect1));
    compShapes.add(std::make_shared<Rectangle>(rect2));

    Matrix matrix;
    matrix.add(std::make_shared<CompositeShape>(compShapes));

    BOOST_CHECK_THROW(matrix.add(matrix[0][0]), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMatrixIndex)
  {
    Rectangle rect1 = {{2, 2}, 2, 2};
    Rectangle rect2 = {{3, -2}, 2, 4};
    Circle circle = {{2, -2}, 3};

    Matrix matrix;
    matrix.add(std::make_shared<Rectangle>(rect1));
    matrix.add(std::make_shared<Rectangle>(rect2));
    matrix.add(std::make_shared<Circle>(circle));

    BOOST_TEST(matrix[0][0]->getArea(), rect1.getArea());
    BOOST_TEST(matrix[0][1]->getArea(), rect2.getArea());
    BOOST_TEST(matrix[1][0]->getArea(), circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(TestMatrixOutOfRangeIndex)
  {
    Circle circle = {{12, 2}, 3};
    Rectangle rect1 = {{-4, 5}, 4, 2};
    Rectangle rect2 = {{6, 2}, 2, 8};

    CompositeShape compShapes;
    compShapes.add(std::make_shared<Circle>(circle));
    compShapes.add(std::make_shared<Rectangle>(rect1));
    compShapes.add(std::make_shared<Rectangle>(rect2));

    Matrix matrix;
    matrix.add(compShapes);

    BOOST_CHECK_THROW(matrix[2], std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
