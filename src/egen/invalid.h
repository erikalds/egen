#ifndef INVALID_H_
#define INVALID_H_

/* Header created: 2009-06-28

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

#include <cmath>
#include <limits>
#include <loki/TypeTraits.h>

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
    return Loki::Select<Loki::TypeTraits<T>::isArith,
      detail::arithmetic_invalid<T>,
      detail::user_defined_invalid<T> >::Result::get_invalid();
  }

  namespace detail
  {
    template<typename T>
    struct similar
    {
      static bool compare(const T& lhs, const T& rhs)
      { return std::abs(lhs - rhs) < 1E-10; }
    };

    template<typename T>
    struct exact_equal
    {
      static bool compare(const T& lhs, const T& rhs)
      { return lhs == rhs; }
    };
  }

  template<typename T>
  bool invalid(const T& value)
  {
    return Loki::Select<Loki::TypeTraits<T>::isFloat,
      detail::similar<T>,
      detail::exact_equal<T> >::Result::compare(invalid<T>(), value);
  }

  template<typename T>
  bool valid(const T& value)
  {
    return !invalid<T>(value);
  }
} // namespace egen

#endif // INVALID_H_
