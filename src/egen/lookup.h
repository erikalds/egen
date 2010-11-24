#ifndef LOOKUP_H_
#define LOOKUP_H_

/* Header created: 2010-11-24

  egen - Erik's generic library
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

#include "egen/invalid.h"

namespace egen
{
  /// Look up \c key in \c a_map.  If \c key is not found, \c default_value is
  /// returned.
  template<typename KeyT, typename ValueT>
  ValueT lookup(const KeyT& key, const std::map<KeyT, ValueT>& a_map,
                const ValueT& default_value = invalid<ValueT>())
  {
    typename std::map<KeyT, ValueT>::const_iterator iter = a_map.find(key);
    if (iter == a_map.end())
      return default_value;

    return iter->second;
  }
} // namespace couped

#endif // LOOKUP_H_
