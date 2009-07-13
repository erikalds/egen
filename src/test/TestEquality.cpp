/* Source file created: 2009-07-10

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

#include <cmath>
#include <boost/test/unit_test.hpp>
#include "egen/equality.h"

BOOST_AUTO_TEST_SUITE(TestEquality);

struct F
{
  F() {}
  ~F() {}
};

BOOST_FIXTURE_TEST_CASE(test_exact_equal, F)
{
  BOOST_CHECK(egen::exact_equal<int>::compare(42, 42));
  BOOST_CHECK(egen::exact_equal<unsigned int>::compare(42U, 42U));
  BOOST_CHECK(egen::exact_equal<short>::compare(42, 42));
  BOOST_CHECK(egen::exact_equal<char>::compare('c', 'c'));
  BOOST_CHECK(egen::exact_equal<long>::compare(42L, 42L));
  BOOST_CHECK(egen::exact_equal<unsigned long long>::compare(42ULL, 42ULL));
  BOOST_CHECK(egen::exact_equal<float>::compare(42.1, 42.1));
  BOOST_CHECK(egen::exact_equal<double>::compare(M_PI, M_PI));
  BOOST_CHECK(egen::exact_equal<bool>::compare(true, true));

  BOOST_CHECK(!egen::exact_equal<int>::compare(42, 43));
  BOOST_CHECK(!egen::exact_equal<unsigned int>::compare(42U, 43U));
  BOOST_CHECK(!egen::exact_equal<short>::compare(42, 43));
  BOOST_CHECK(!egen::exact_equal<char>::compare('c', 'd'));
  BOOST_CHECK(!egen::exact_equal<long>::compare(42L, 43L));
  BOOST_CHECK(!egen::exact_equal<unsigned long long>::compare(42ULL, 43ULL));
  BOOST_CHECK(!egen::exact_equal<float>::compare(1.0,
						 1.0 + std::numeric_limits<float>::epsilon()));
  BOOST_CHECK(!egen::exact_equal<double>::compare(1.0,
						  1.0 + std::numeric_limits<double>::epsilon()));
  BOOST_CHECK(!egen::exact_equal<bool>::compare(true, false));
}

BOOST_FIXTURE_TEST_CASE(test_similar, F)
{
  BOOST_CHECK(egen::similar<double>::compare(1.0, 1.0 + std::numeric_limits<double>::epsilon()));
  BOOST_CHECK(egen::similar<double>::compare(1.0, 1.0 + 0.9E-10));
  BOOST_CHECK(!egen::similar<double>::compare(1.0, 1.0 + 1.0E-10));
  BOOST_CHECK(egen::similar<double>::compare(1.0, 1.0 - std::numeric_limits<double>::epsilon()));
  BOOST_CHECK(egen::similar<double>::compare(1.0, 1.0 - 0.9E-10));
  BOOST_CHECK(!egen::similar<double>::compare(1.0, 1.0 - 1.0E-10));

  BOOST_CHECK(egen::similar<float>::compare(1.0, 1.0 + std::numeric_limits<float>::epsilon()));
  BOOST_CHECK(egen::similar<float>::compare(1.0, 1.0 + 0.9E-10));
  BOOST_CHECK(egen::similar<float>::compare(1.0, 1.0 + 1.0E-10));
  BOOST_CHECK(egen::similar<float>::compare(1.0, 1.0 + 1.0E-6));
  BOOST_CHECK(!egen::similar<float>::compare(1.0, 1.0 + 1.1E-6)); // round off/precision error
  BOOST_CHECK(egen::similar<float>::compare(1.0, 1.0 - std::numeric_limits<float>::epsilon()));
  BOOST_CHECK(egen::similar<float>::compare(1.0, 1.0 - 0.9E-10));
  BOOST_CHECK(egen::similar<float>::compare(1.0, 1.0 - 1.0E-10));
  BOOST_CHECK(egen::similar<float>::compare(1.0, 1.0 - 0.9E-6));
  BOOST_CHECK(!egen::similar<float>::compare(1.0, 1.0 - 1.0E-6));
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
