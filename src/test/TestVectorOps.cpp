/* Source file created: 2012-12-08

  egen - Erik's generic library
  Copyright (C) 2012 Erik Åldstedt Sund

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  To contact the author, e-mail at erikalds@gmail.com or through
  regular mail:
    Erik Åldstedt Sund
    Darres veg 14
    NO-7540 KLÆBU
    NORWAY
*/

#include <boost/test/unit_test.hpp>

#include "egen/Angle.h"
#include "egen/InvalidPointOperation.h"
#include "egen/InvalidVectorOperation.h"
#include "egen/Point.h"
#include "egen/Vector.h"
#include "egen/vector_ops.h"

using namespace egen;

BOOST_AUTO_TEST_SUITE(testVectorOps)

struct F
{
  F() {}
  ~F() {}

  void check_2d_unit_vector(const Vector<double>& v, double x, double y)
  {
    BOOST_CHECK_LT(std::abs(1.0 - v.length()), 1.0e-6);
    BOOST_CHECK_LT(std::abs(0.0 - v.z()), 1.0e-6);
    BOOST_CHECK_LT(std::abs(x - v.x()), 1.0e-6);
    BOOST_CHECK_LT(std::abs(y - v.y()), 1.0e-6);
  }
};

BOOST_FIXTURE_TEST_CASE(zeroAngle_unitVectorAlongXAxis, F)
{
  check_2d_unit_vector(unit_vector(Angle::deg(0)), 1, 0);
}

BOOST_FIXTURE_TEST_CASE(ninetyDegAngle_unitVectorAlongYAxis, F)
{
  check_2d_unit_vector(unit_vector(Angle::deg(90)), 0, 1);
}

BOOST_FIXTURE_TEST_CASE(oneHundredAndEightyDeg_unitVectorAlongNegXAxis, F)
{
  check_2d_unit_vector(unit_vector(Angle::deg(180)), -1, 0);
}

BOOST_FIXTURE_TEST_CASE(twoHundredAndSeventyDeg_unitVectorAlongNegYAxis, F)
{
  check_2d_unit_vector(unit_vector(Angle::deg(270)), 0, -1);
}

BOOST_FIXTURE_TEST_CASE(genericAngle_correctUnitVector, F)
{
  check_2d_unit_vector(unit_vector(Angle::deg(42)), 0.74314483, 0.66913061);
  check_2d_unit_vector(unit_vector(Angle::deg(232)), -0.61566148, -0.78801075);
}

BOOST_FIXTURE_TEST_CASE(twoThreeDPointDifference_givesThreeDVector, F)
{
  Point<int> p0(10, 20, 30);
  Point<int> p1(4, 5, 6);
  BOOST_CHECK_EQUAL(Vector<int>(6, 15, 24), p0 - p1);
  BOOST_CHECK_EQUAL(Vector<int>(-6, -15, -24), p1 - p0);
}

BOOST_FIXTURE_TEST_CASE(twoTwoDPointsDifference_gives2DVector, F)
{
  Point<int> p0(1, 2);
  Point<int> p1(4, 5);
  BOOST_CHECK_EQUAL(Vector<int>(-3, -3), p0 - p1);
  BOOST_CHECK_EQUAL(Vector<int>(3, 3), p1 - p0);
}

BOOST_FIXTURE_TEST_CASE(invalidPointDifference_throwsException, F)
{
  Point<int> p0(1, 2);
  Point<int> invalid_pt = invalid<Point<int>>();
  BOOST_CHECK_EXCEPTION(p0 - invalid_pt, InvalidPointOperation,
                        [](const InvalidPointOperation& ipo)
                        {
                          return std::string(ipo.what()).find("ight hand side")
                            != std::string::npos;
                        });
  BOOST_CHECK_EXCEPTION(invalid_pt - p0, InvalidPointOperation,
                        [](const InvalidPointOperation& ipo)
                        {
                          return std::string(ipo.what()).find("eft hand side")
                            != std::string::npos;
                        });
  BOOST_CHECK_EXCEPTION(invalid_pt - invalid_pt, InvalidPointOperation,
                        [](const InvalidPointOperation& ipo)
                        {
                          return std::string(ipo.what()).find("oth sides")
                            != std::string::npos;
                        });
}

BOOST_FIXTURE_TEST_CASE(twoDPointPlusTwoDVector_isTwoDPoint, F)
{
  Point<int> p0(10, 10);
  Point<int> p1(20, 20);
  Vector<int> v0(20, 42);
  Vector<int> v1(0, 22);
  BOOST_CHECK_EQUAL(Point<int>(30, 52), p0 + v0);
  BOOST_CHECK_EQUAL(Point<int>(20, 42), p1 + v1);
}

BOOST_FIXTURE_TEST_CASE(threeDPointPlusThreeDVector_isThreeDPoint, F)
{
  Point<int> p0(10, 10, 10);
  Point<int> p1(20, 20, 20);
  Vector<int> v0(0, 10, 20);
  Vector<int> v1(4, 5, 6);
  BOOST_CHECK_EQUAL(Point<int>(10, 20, 30), p0 + v0);
  BOOST_CHECK_EQUAL(Point<int>(24, 25, 26), p1 + v1);
}

BOOST_FIXTURE_TEST_CASE(pointPlusVector_handlesInvalid, F)
{
  Point<int> p = invalid<Point<int>>();
  Vector<int> v = invalid<Vector<int>>();
  BOOST_CHECK_EXCEPTION(p + Vector<int>(0, 0), InvalidPointOperation,
                        [](const InvalidPointOperation& ipo)
                        {
                          const std::string what(ipo.what());
                          const std::size_t addpos(what.find(" add "));
                          const std::size_t vecpos(what.find(" vector "));
                          const std::size_t invpos(what.rfind("invalid point"));
                          return addpos != std::string::npos
                            && vecpos != std::string::npos
                            && invpos != std::string::npos
                            && addpos < vecpos
                            && vecpos < invpos;
                        });
  BOOST_CHECK_EXCEPTION(Point<int>(0, 0) + v, InvalidVectorOperation,
                        [](const InvalidVectorOperation& ivo)
                        {
                          const std::string what(ivo.what());
                          const std::size_t addpos(what.find(" add "));
                          const std::size_t invpos
                            = what.rfind(" invalid vector ");
                          const std::size_t pntpos(what.find(" point"));
                          return addpos != std::string::npos
                            && invpos != std::string::npos
                            && pntpos != std::string::npos
                            && addpos < invpos
                            && invpos < pntpos;
                        });
  BOOST_CHECK_EXCEPTION(p + v, InvalidVectorOperation,
                        [](const InvalidVectorOperation& ivo)
                        {
                          const std::string what(ivo.what());
                          const std::size_t addpos(what.find(" add "));
                          const std::size_t ivcpos
                            = what.rfind(" invalid vector ");
                          const std::size_t iptpos
                            = what.rfind(" invalid point");
                          return addpos != std::string::npos
                            && ivcpos != std::string::npos
                            && iptpos != std::string::npos
                            && addpos < ivcpos
                            && ivcpos < iptpos;
                        });
}

BOOST_FIXTURE_TEST_CASE(negateVector, F)
{
  Vector<int> v0(10, 10);
  Vector<int> v1(-100, -200, -42);
  BOOST_CHECK_EQUAL(Vector<int>(-10, -10), -v0);
  BOOST_CHECK_EQUAL(Vector<int>(100, 200, 42), -v1);

  BOOST_CHECK_EXCEPTION(-invalid<Vector<int>>(), InvalidVectorOperation,
                        [](const InvalidVectorOperation& ivo)
                        { return std::string(ivo.what()).find("Cannot negate invalid vector.")
                            != std::string::npos; });
}

BOOST_FIXTURE_TEST_CASE(pointMinusVector, F)
{
  BOOST_CHECK_EQUAL(Point<int>(32, 42), Point<int>(52, 52) - Vector<int>(20, 10));
  BOOST_CHECK_EQUAL(Point<int>(1, 2, 3), Point<int>(4, 3, 2) - Vector<int>(3, 1, -1));
  BOOST_CHECK_EXCEPTION(invalid<Point<int>>() - Vector<int>(0, 0, 0),
                        InvalidPointOperation,
                        [](const InvalidPointOperation& ipo)
                        {
                          const std::string what(ipo.what());
                          const std::size_t subpos(what.find(" subtract "));
                          const std::size_t vecpos(what.find(" vector "));
                          const std::size_t invpos(what.rfind("invalid point"));
                          return subpos != std::string::npos
                            && vecpos != std::string::npos
                            && invpos != std::string::npos
                            && subpos < vecpos
                            && vecpos < invpos;
                        });
  BOOST_CHECK_EXCEPTION(Point<int>(0, 0) - invalid<Vector<int>>(),
                        InvalidVectorOperation,
                        [](const InvalidVectorOperation& ivo)
                        {
                          const std::string what(ivo.what());
                          const std::size_t subpos(what.find(" subtract "));
                          const std::size_t invpos
                            = what.rfind(" invalid vector ");
                          const std::size_t pntpos(what.find(" point"));
                          return subpos != std::string::npos
                            && invpos != std::string::npos
                            && pntpos != std::string::npos
                            && subpos < invpos
                            && invpos < pntpos;
                        });
  BOOST_CHECK_EXCEPTION(invalid<Point<int> >() - invalid<Vector<int> >(),
                        InvalidVectorOperation,
                        [](const InvalidVectorOperation& ivo)
                        {
                          const std::string what(ivo.what());
                          const std::size_t subpos(what.find(" subtract "));
                          const std::size_t ivcpos
                            = what.rfind(" invalid vector ");
                          const std::size_t iptpos
                            = what.rfind(" invalid point");
                          return subpos != std::string::npos
                            && ivcpos != std::string::npos
                            && iptpos != std::string::npos
                            && subpos < ivcpos
                            && ivcpos < iptpos;
                        });
}

BOOST_AUTO_TEST_SUITE_END()

/*

  The defined macros are:

  BOOST_ERROR(message)
  BOOST_FAIL(message)
  BOOST_IS_DEFINED(symbol)

  BOOST_level(condition)
  BOOST_level_MESSAGE(condition, message)
  BOOST_level_THROW(expression, exception_type)
  BOOST_level_EXCEPTION(expression, exception_type, P)
  BOOST_level_NO_THROW(expression)
  BOOST_level_EQUAL(left_expression, right_expression)
  BOOST_level_NE(left_expression, right_expression)
  BOOST_level_LT(left_expression, right_expression)
  BOOST_level_LE(left_expression, right_expression)
  BOOST_level_GT(left_expression, right_expression)
  BOOST_level_GE(left_expression, right_expression)
  BOOST_level_CLOSE(left_expression, right_expression, percentage)
  BOOST_level_CLOSE_FRACTION(left_expression, right_expression, fraction)
  BOOST_level_SMALL(left_expression, right_expression, T)
  BOOST_level_PREDICATE(predicate_function, arguments)
  BOOST_level_EQUAL_COLLECTIONS(left_begin, left_end, right_begin, right_end)
  BOOST_level_BITWISE_EQUAL(left_expression, right_expression)

  Three levels of errors are defined:

  Level   | Errors counter | Test execution
  --------+----------------+---------------
  WARN    | not affected   | continues
  CHECK   | increased      | continues
  REQUIRE | increased      | aborts

 */
