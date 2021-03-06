/* Source file created: 2009-07-08

  egen - Erik's generic library
  Copyright (C) 2009 Erik �ldstedt Sund

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
#include "egen/invalid.h"

BOOST_AUTO_TEST_SUITE(TestInvalid)

struct F
{
  F() {}
  ~F() {}
};

BOOST_FIXTURE_TEST_CASE(test_invalid_int, F)
{
  BOOST_CHECK_NE(egen::invalid<int>(), egen::invalid<unsigned int>());
  BOOST_REQUIRE(egen::valid(42));
  BOOST_REQUIRE(!egen::invalid(0));
  BOOST_REQUIRE(egen::invalid(egen::invalid<int>()));
}

BOOST_FIXTURE_TEST_CASE(test_invalid_double, F)
{
  BOOST_CHECK_NE(egen::invalid<float>(), egen::invalid<double>());
  BOOST_REQUIRE(egen::valid(42.0));
  BOOST_REQUIRE(!egen::invalid(0.0));
  BOOST_REQUIRE(egen::invalid(egen::invalid<double>()));
}

namespace {
  struct A {
    int m_a;

    explicit A(int a) : m_a(a) {}

    static A invalid_value() { return A(egen::invalid<int>()); }
  };

  bool operator==(const A& lhs, const A& rhs) { return lhs.m_a == rhs.m_a; }

  std::ostream& operator<<(std::ostream& out, const A& x)
  { return out << "A(" << x.m_a << ")"; }
}

BOOST_FIXTURE_TEST_CASE(test_invalid_user_defined_class, F)
{
  BOOST_CHECK_EQUAL(A::invalid_value(), egen::invalid<A>());
}

BOOST_FIXTURE_TEST_CASE(test_invalid_string, F)
{
  BOOST_CHECK(egen::invalid<std::string>(egen::invalid<std::string>()));
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
