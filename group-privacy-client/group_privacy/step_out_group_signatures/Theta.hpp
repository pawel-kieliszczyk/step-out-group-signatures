/**
 * @file Theta.hpp
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

#ifndef THETA_HPP
#define	THETA_HPP

#include "../mpi/BigInteger.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/tuple/tuple.hpp>

#include <vector>

class ThetaElement : public boost::tuple<BigInteger, BigInteger>
{
    friend class boost::serialization::access;
public:
    ThetaElement();
    ThetaElement(const BigInteger& first, const BigInteger& second);
    ThetaElement(const ThetaElement& element);
    ThetaElement& operator=(const ThetaElement& element);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & boost::get<0>(*this);
        archive & boost::get<1>(*this);
    }
};

bool operator==(const ThetaElement& left, const ThetaElement& right);

class Theta : public std::vector<ThetaElement>
{
    friend class boost::serialization::access;
public:
    Theta();
    Theta(const Theta& theta);
    Theta& operator=(const Theta& theta);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & dynamic_cast<std::vector<ThetaElement>&>(*this);
    }
};

#endif // THETA_HPP
