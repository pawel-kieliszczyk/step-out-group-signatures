/**
 * @file Delta.hpp
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

#ifndef DELTA_HPP
#define	DELTA_HPP

#include "../mpi/BigInteger.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/tuple/tuple.hpp>

#include <vector>

class DeltaElement : public boost::tuple<BigInteger, BigInteger>
{
    friend class boost::serialization::access;
public:
    DeltaElement();
    DeltaElement(const BigInteger& i, const BigInteger& grLti);
    DeltaElement(const DeltaElement& element);
    DeltaElement& operator=(const DeltaElement& element);
    const BigInteger& i() const;
    BigInteger& i();
    const BigInteger& grLti() const;
    BigInteger& grLti();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & i();
        archive & grLti();
    }
};

class Delta : public std::vector<DeltaElement>
{
    friend class boost::serialization::access;
public:
    Delta();
    Delta(const Delta& delta);
    Delta& operator=(const Delta& delta);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & dynamic_cast<std::vector<DeltaElement>&>(*this);
    }
};

#endif // DELTA_HPP
