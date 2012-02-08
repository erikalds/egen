#ifndef EQUALITY_H_
#define EQUALITY_H_

/* Header created: 2009-07-10

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

namespace egen
{
  template<typename T>
  struct exact_equal
  {
    static bool compare(const T& lhs, const T& rhs)
    { return lhs == rhs; }
  };

  namespace detail
  {
    template<typename T>
    struct small_limit;

    template<>
    struct small_limit<float>
    {
      static constexpr float value = 1.0E-6;
    };

    template<>
    struct small_limit<double>
    {
      static constexpr double value = 1.0E-10;
    };
  }

  template<typename T>
  struct similar
  {
    static bool compare(const T& lhs, const T& rhs)
    { return std::abs(lhs - rhs) < detail::small_limit<T>::value; }
  };
} // namespace egen

#endif // EQUALITY_H_
