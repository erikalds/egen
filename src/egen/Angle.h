#ifndef ANGLE_H_
#define ANGLE_H_

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

#include <iosfwd>

namespace egen
{
  class Angle
  {
  public:
    static Angle deg(double angle);
    static Angle rad(double angle);

    bool operator==(const Angle& other) const;
    bool operator<(const Angle& other) const;
    Angle operator-(const Angle& other) const;
    Angle operator*(double scalar) const;

    friend std::ostream& operator<<(std::ostream& out, const Angle& a);

  private:
    Angle(double rad);

    double angle;
  };

  std::ostream& operator<<(std::ostream& out, const Angle& a);

  inline bool operator!=(const Angle& alpha, const Angle& beta)
  { return !(alpha == beta); }

  inline bool operator<=(const Angle& alpha, const Angle& beta)
  { return alpha < beta || alpha == beta; }
  inline bool operator>(const Angle& alpha, const Angle& beta)
  { return !(alpha <= beta); }
  inline bool operator>=(const Angle& alpha, const Angle& beta)
  { return !(alpha < beta); }

  inline Angle operator*(double scalar, const Angle& alpha)
  { return alpha * scalar; }
  inline Angle operator-(const Angle& alpha)
  { return alpha * -1; }
} // namespace egen

#endif // ANGLE_H_
