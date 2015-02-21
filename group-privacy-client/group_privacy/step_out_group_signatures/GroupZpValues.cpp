/**
 * @file GroupZpValues.cpp
 * @author Pawel Kieliszczyk <pawel.kieliszczyk@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * Copyright (C) 2011 Pawel Kieliszczyk
 *
 * This file is part of Group Privacy.
 *
 * Group Privacy is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Group Privacy is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Group Privacy. If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 */

#include "GroupZpValues.hpp"

GroupZpValues::GroupZpValues() : p(), q(), g()
{
}

GroupZpValues::GroupZpValues(const GroupZpValues& groupZpValues)
    : p(groupZpValues.p),
      q(groupZpValues.q),
      g(groupZpValues.q)
{
}

GroupZpValues& GroupZpValues::operator=(const GroupZpValues& groupZpValues)
{
    p = groupZpValues.p;
    q = groupZpValues.q;
    g = groupZpValues.g;
    return *this;
}
