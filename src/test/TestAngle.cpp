/* Source file created: 2012-12-08

  egen - Erik's generic library
  Copyright (C) 2012 Erik �ldstedt Sund

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
    Erik �ldstedt Sund
    Darres veg 14
    NO-7540 KL�BU
    NORWAY
*/

#include <boost/test/unit_test.hpp>

#include "egen/Angle.h"

using namespace egen;

BOOST_AUTO_TEST_SUITE(testAngle)

struct F
{
  F() {}
  ~F() {}
};

BOOST_FIXTURE_TEST_CASE(twoZeroAngles_areEqual, F)
{
  Angle alpha = Angle::degrees(0);
  Angle beta = Angle::degrees(0);
  BOOST_CHECK_EQUAL(alpha, beta);
}

BOOST_FIXTURE_TEST_CASE(twoDifferentAngles_areNotEqual, F)
{
  Angle alpha = Angle::degrees(0);
  Angle beta = Angle::degrees(1);
  BOOST_CHECK_NE(alpha, beta);
}

BOOST_FIXTURE_TEST_CASE(twoEqualAnglesRadiansAndDegrees_areEqual, F)
{
  Angle alpha = Angle::degrees(90);
  Angle beta = Angle::radians(M_PI / 2);
  BOOST_CHECK_EQUAL(alpha, beta);
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
