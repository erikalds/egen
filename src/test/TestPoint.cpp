/* Source file created: 2009-07-09

  egen - Erik's generic library
  Copyright (C) 2009 Erik Åldstedt Sund

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
#include "egen/Point.h"

BOOST_AUTO_TEST_SUITE(TestPoint)

struct F
{
  F() {}
  ~F() {}
};

BOOST_FIXTURE_TEST_CASE(test_invalid_point, F)
{
  egen::Point<int> inv = egen::invalid<egen::Point<int> >();
  BOOST_CHECK_EQUAL(egen::invalid<int>(), inv.x());
  BOOST_CHECK_EQUAL(egen::invalid<int>(), inv.y());
  BOOST_CHECK_EQUAL(egen::invalid<int>(), inv.z());
}

BOOST_FIXTURE_TEST_CASE(test_2d_point_zero_z, F)
{
  egen::Point<double> p(2.0, 0.0);
  BOOST_CHECK_EQUAL(0.0, p.z());
}

BOOST_FIXTURE_TEST_CASE(test_ostream_operator, F)
{
  egen::Point<double> p2d(2.2, 1.0);
  egen::Point<double> p3d(3.0, 2.0, 1.0);
  std::ostringstream actual2d;
  actual2d << p2d;
  BOOST_CHECK_EQUAL("(2.2, 1)", actual2d.str());
  std::ostringstream actual3d;
  actual3d << p3d;
  BOOST_CHECK_EQUAL("(3, 2, 1)", actual3d.str());
}

BOOST_FIXTURE_TEST_CASE(test_equality_operator, F)
{
  egen::Point<int> p0(2, 0);
  egen::Point<int> p1(p0.x(), p0.y());
  egen::Point<int> p2(p1.x(), p1.y() + 1);
  BOOST_CHECK_EQUAL(p0, p1);
  BOOST_CHECK(!(p1 == p2));
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
