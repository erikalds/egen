/* Source file created: 2009-07-08

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

#include <boost/lexical_cast.hpp>
#include <boost/progress.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/unit_test_monitor.hpp>

#define BOOST_TEST_SOURCE
#define BOOST_TEST_NO_MAIN
#include <boost/test/impl/unit_test_main.ipp>
#include <boost/test/impl/framework.ipp>
#undef BOOST_TEST_SOURCE
#undef BOOST_TEST_NO_MAIN

using namespace boost::unit_test;

void std_exception_handler(const std::exception& e)
{
  BOOST_ERROR(std::string("Caught std::exception: ") + e.what());
}

test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
  unit_test_monitor.register_exception_translator<std::exception>(&std_exception_handler);
  return 0;
}

int main(int argc, char* argv[])
{
  boost::progress_timer time_display;
  return ::boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
