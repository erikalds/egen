#ifndef COORDINATE_H_
#define COORDINATE_H_

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

#include <ostream>
#include "egen/invalid.h"

namespace egen
{
  template<typename T>
  class Coordinate
  {
  public:
    Coordinate() : m_x(invalid<T>()), m_y(invalid<T>()), m_z(invalid<T>()) {}
    explicit Coordinate(const T& x, const T& y, const T& z=invalid<T>()) :
      m_x(x), m_y(y), m_z(z) {}

    T  x() const { return m_x; }
    T& x()       { return m_x; }
    T  y() const { return m_y; }
    T& y()       { return m_y; }
    T  z() const { return m_z; }
    T& z()       { return m_z; }

    static Coordinate invalid_value() { return Coordinate(); }

    template<typename U>
    Coordinate<U> scale(const U& x_scale, const U& y_scale, const U& z_scale=invalid<U>());

  private:
    T m_x;
    T m_y;
    T m_z;
  };

  template<typename T>
  bool operator==(const Coordinate<T>& lhs, const Coordinate<T>& rhs)
  { return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z(); }

  template<typename T>
  std::ostream& operator<<(std::ostream& out, const Coordinate<T>& p);
} // namespace egen

// implementations

namespace egen {
  template<typename T>
  template<typename U>
  Coordinate<U> Coordinate<T>::scale(const U& x_scale, const U& y_scale, const U& z_scale)
  {
    if (invalid(*this) || valid(z_scale) != valid(z()))
      return invalid<Coordinate<U> >();

    Coordinate<U> scaled;
    scaled.x() = U(x()) * x_scale;
    scaled.y() = U(y()) * y_scale;
    if (valid(z_scale))
      scaled.z() = U(z()) * z_scale;

    return scaled;
  }

  template<typename T>
  std::ostream& operator<<(std::ostream& out, const Coordinate<T>& p)
  {
    if (invalid(p))
      return out << "invalid point";

    out << "(" << p.x() << ", " << p.y();
    if (valid(p.z()))
      out << ", " << p.z();
    return out << ")";
  }
} // namespace egen

#endif // COORDINATE_H_
