#ifndef VECTOR_H_
#define VECTOR_H_

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

#include "egen/Coordinate.h"

namespace egen
{
  template<typename T>
  class Vector : public Coordinate<T>
  {
  public:
    Vector() : Coordinate<T>() {}
    Vector(const T& x, const T& y, const T& z=0) :
      Coordinate<T>(x, y, z) {}
    Vector(const Coordinate<T>& other) : Coordinate<T>(other) {}
    operator Coordinate<T>() const { return *this; }

    double length() const;
  };
} // namespace egen


template<typename T>
double egen::Vector<T>::length() const
{
  double l = this->x() * this->x() + this->y() * this->y();
  if (valid(this->z()))
    l += this->z() * this->z();
  return std::sqrt(l);
}

#endif // VECTOR_H_
