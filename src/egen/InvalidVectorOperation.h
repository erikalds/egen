#ifndef INVALIDVECTOROPERATION_H_
#define INVALIDVECTOROPERATION_H_

/* Header created: 2012-12-22

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

#include <stdexcept>

namespace egen
{
  class InvalidVectorOperation : public std::invalid_argument
  {
  public:
    InvalidVectorOperation(const std::string& msg) :
      std::invalid_argument("An invalid vector was given to a function. " + msg)
    {}
  };
} // namespace egen

#endif // INVALIDVECTOROPERATION_H_
