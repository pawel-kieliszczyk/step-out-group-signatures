/**
 * @file GroupZpValues.hpp
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

#ifndef GROUPZPVALUES_HPP
#define	GROUPZPVALUES_HPP

#include "../mpi/BigInteger.hpp"

#include <boost/serialization/access.hpp>

struct GroupZpValues
{
    GroupZpValues();
    GroupZpValues(const GroupZpValues& groupZpValues);
    GroupZpValues& operator=(const GroupZpValues& groupZpValues);

    BigInteger p; /**< Prime number that indicates Zp Group. */
    BigInteger q; /**< Prime number such that 2q+1 = p. */
    BigInteger g; /**< Generator of a subgroup G of a group Zp of order q. */
private:
    friend class boost::serialization::access;

    /**
     * Serializes the whole sctructure using boost::serialization.
     *
     * @param archive Archiver.
     * @param version Version of the serialized object.
     */
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & p;
        archive & q;
        archive & g;
    }
};

#endif // GROUPZPVALUES_HPP
