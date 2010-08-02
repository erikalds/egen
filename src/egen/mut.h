#ifndef MUT_H_
#define MUT_H_

/* Header created: 2010-08-02

  hourtracker - C++ web application for administration of work hours
  Copyright (C) 2010 Erik Åldstedt Sund

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
  namespace mut
  {

    /// \c interval is generally the boost::numeric::interval.  But the only
    /// needed functionality in scale are the member functions \c lower and \c
    /// upper.
    template<typename T, typename interval>
    T scale(const T& val, const interval& from, const interval& to)
    {
      return to.lower() + (double(val - from.lower()) /
                           double(from.upper() - from.lower())) *
        double(to.upper() - to.lower());
    }
  } // namespace mut
} // namespace egen

#endif // MUT_H_
