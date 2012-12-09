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
