#ifndef VECTOR_OPS_H_
#define VECTOR_OPS_H_

/* Header created: 2012-12-08

  egen - Erik's generic library
  Copyright (C) 2012 Erik Åldstedt Sund

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

#include "egen/InvalidPointOperation.h"
#include "egen/InvalidVectorOperation.h"
#include "egen/Point.h"
#include "egen/Vector.h"

// --- interface ---
namespace egen
{
  class Angle;

  Vector<double> unit_vector(const Angle& alpha);

  template<typename T>
  Vector<T> operator-(const Vector<T>& v);

  template<typename T>
  Vector<T> operator-(const Point<T>& lhs, const Point<T>& rhs);

  template<typename T>
  Point<T> operator+(const Point<T>& lhs, const Vector<T>& rhs);
} // namespace egen


// --- inline implementations ---

template<typename T>
egen::Vector<T> egen::operator-(const egen::Vector<T>& v)
{
  if (egen::invalid(v))
    throw egen::InvalidVectorOperation("Cannot negate invalid vector.");
  return egen::Vector<T>(-v.x(), -v.y(), -v.z());
}

template<typename T>
egen::Vector<T> egen::operator-(const egen::Point<T>& lhs,
                                const egen::Point<T>& rhs)
{
  const std::string repeated_string(" of difference of points operator.");
  if (invalid(lhs) && invalid(rhs))
    throw InvalidPointOperation("Both sides" + repeated_string);
  if (invalid(lhs))
    throw InvalidPointOperation("Left hand side" + repeated_string);
  if (invalid(rhs))
    throw InvalidPointOperation("Right hand side" + repeated_string);

  return egen::Vector<T>(lhs.x() - rhs.x(),
                         lhs.y() - rhs.y(),
                         lhs.z() - rhs.z());
}

template<typename T>
egen::Point<T> egen::operator+(const egen::Point<T>& lhs,
                               const egen::Vector<T>& rhs)
{
  if (invalid(lhs) && invalid(rhs))
    throw InvalidVectorOperation("Tried to add an invalid vector to an "
                                 "invalid point.");
  if (invalid(lhs))
    throw InvalidPointOperation("Tried to add a vector to an invalid point.");
  if (invalid(rhs))
    throw InvalidVectorOperation("Tried to add an invalid vector to a point.");
  return egen::Point<T>(lhs.x() + rhs.x(), lhs.y() + rhs.y(),
                        lhs.z() + rhs.z());
}

#endif // VECTOR_OPS_H_
