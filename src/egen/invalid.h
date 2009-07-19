#ifndef INVALID_H_
#define INVALID_H_

/* Header created: 2009-06-28

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
#include <limits>
#include <boost/mpl/if.hpp>
#include <boost/type_traits.hpp>
#include "egen/equality.h"

// interface

namespace egen
{
  /// Get an invalid value of type T.
  template<typename T>
  T invalid();

  /// Check if value is an invalid value.
  template<typename T>
  bool invalid(const T& value);

  /// Check if value is a valid value.
  template<typename T>
  bool valid(const T& value);
} // namespace egen

// implementation

namespace egen
{
  namespace detail
  {
    template<typename T>
    struct arithmetic_invalid
    {
      static T get_invalid() { return std::numeric_limits<T>::max(); }
    };

    template<typename T>
    struct user_defined_invalid
    {
      static T get_invalid() { return T::invalid_value(); }
    };
  }

  template<typename T>
  T invalid()
  {
    return boost::mpl::if_<boost::is_arithmetic<T>,
      detail::arithmetic_invalid<T>,
      detail::user_defined_invalid<T> >::type::get_invalid();
  }

  template<typename T>
  bool invalid(const T& value)
  {
    return boost::mpl::if_<boost::is_floating_point<T>,
      similar<T>,
      exact_equal<T> >::type::compare(invalid<T>(), value);
  }

  template<typename T>
  bool valid(const T& value)
  {
    return !invalid<T>(value);
  }
} // namespace egen

#endif // INVALID_H_
