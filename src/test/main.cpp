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

void usage_and_exit(const std::string& prog_name, const std::string& msg,
		    int exit_code)
{
  std::cout << prog_name << ": unit test execution application." << std::endl;
  std::cout << std::endl;
  if (!msg.empty())
  {
    std::cout << "Exit reason: " << msg << std::endl;
    std::cout << std::endl;
  }

  std::cout << "Available options are:" << std::endl;
  std::cout << " --level <[0-8]>\tSet log level (0: verbose, 8 nothing)"
	    << std::endl;
  std::cout << " --format <(CLF|XML)>\tSet output format." << std::endl;
  std::cout << " -h|--help\t\tShow this help message." << std::endl;
  std::cout << std::endl;
  exit(exit_code);
}

test_suite* init_unit_test_suite(int argc, char* argv[])
{
  unit_test_monitor.register_exception_translator<std::exception>(&std_exception_handler);

  log_level level = log_warnings;
  output_format format = CLF;
  bool progress = false;
  try
  {
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i] == std::string("--level"))
      {
	if (i >= argc - 1)
	  throw std::runtime_error("Missing argument to --level.");

	int n = boost::lexical_cast<int>(argv[++i]);
	if (n >= 0 && n <= 8)
	  level = log_level(n);
	else
	  throw std::runtime_error("--level argument out of range.");
      }
      else if (argv[i] == std::string("--format"))
      {
	if (i >= argc - 1)
	  throw std::runtime_error("Missing argument to --format.");

	std::string s(argv[++i]);
	if (s == "CLF")
	  format = CLF;
	else if (s == "XML")
	  format = XML;
	else
	  throw std::runtime_error("--format argument not recognized.");
      }
      else if (argv[i] == std::string("--help") || argv[i] == std::string("-h"))
      {
	throw 0;
      }
      else if (argv[i] == std::string("--progress"))
      {
	progress = true;
      }
    }
  }
  catch (const int& i)
  {
    usage_and_exit(argv[0], "", i);
  }
  catch (const std::bad_cast& e)
  {
    usage_and_exit(argv[0], e.what(), -2);
  }
  catch (const std::runtime_error& e)
  {
    usage_and_exit(argv[0], e.what(), -1);
  }

  unit_test_log_t::instance().set_threshold_level(level);
  unit_test_log_t::instance().set_format(format);
  if (progress)
    framework::register_observer(progress_monitor_t::instance());
  
  return 0;
}

int main(int argc, char* argv[])
{
  return ::boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
