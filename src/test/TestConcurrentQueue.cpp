/* Source file created: 2011-07-06

  egen - Erik's generic library
  Copyright (C) 2011 Erik Åldstedt Sund

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

#include "egen/ConcurrentQueue.h"
#include <boost/test/unit_test.hpp>
#include <vector>

using namespace std;

BOOST_AUTO_TEST_SUITE(testConcurrentQueue);

struct F
{
  F() : queue() {}
  ~F() {}

  egen::ConcurrentQueue<int> queue;
};

BOOST_FIXTURE_TEST_CASE(test_empty_queue, F)
{
  BOOST_CHECK(!queue.pop_front());
}

BOOST_FIXTURE_TEST_CASE(test_push_pop_yields_empty, F)
{
  queue.push_back(42);
  queue.pop_front();
  BOOST_CHECK(!queue.pop_front());
}

BOOST_FIXTURE_TEST_CASE(test_push_pops_valid, F)
{
  queue.push_back(42);
  BOOST_CHECK(bool(queue.pop_front()));
}

BOOST_FIXTURE_TEST_CASE(test_push_pop_same_val, F)
{
  int val = 42;
  queue.push_back(val);
  BOOST_CHECK_EQUAL(val, queue.pop_front().get());
}

BOOST_FIXTURE_TEST_CASE(test_is_fifo, F)
{
  vector<int> values = { 2, 4, 6, 8, 42 };
  for (auto iter = values.begin(); iter != values.end(); ++iter)
    queue.push_back(*iter);
  for (auto iter = values.begin(); iter != values.end(); ++iter)
  {
    boost::optional<int> val = queue.pop_front();
    BOOST_REQUIRE(bool(val));
    BOOST_CHECK_EQUAL(*iter, val.get());
  }
  BOOST_CHECK(!queue.pop_front());
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
