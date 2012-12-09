/* Source file created: 2009-06-28

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

#include "egen/Angle.h"
#include <cmath>
#include <ostream>

namespace egen
{
  namespace
  {
    inline double rad2deg(double rad)
    {
      return rad * 180 / M_PI;
    }

    inline double deg2rad(double deg)
    {
      return deg * M_PI / 180;
    }
  }

  Angle Angle::deg(double angle)
  {
    return Angle(deg2rad(angle));
  }

  Angle Angle::rad(double angle)
  {
    return Angle(angle);
  }

  bool Angle::operator==(const Angle& other) const
  {
    return angle == other.angle;
  }

  bool Angle::operator<(const Angle& other) const
  {
    return angle < other.angle;
  }

  Angle Angle::operator-(const Angle& other) const
  {
    return angle - other.angle;
  }

  Angle Angle::operator*(double scalar) const
  {
    return angle * scalar;
  }

  Angle& Angle::operator+=(const Angle& other)
  {
    angle += other.angle;
    return *this;
  }

  Angle::Angle(double rad) :
    angle(rad)
  {
  }

  std::ostream& operator<<(std::ostream& out, const Angle& a)
  {
    return out << rad2deg(a.angle) << " deg";
  }

} // namespace egen
