/**
 * @file PublishedValues.cpp
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

#include "PublishedValues.hpp"

PublishedValues::PublishedValues()
    : boost::tuple<BigInteger, BigInteger, BigInteger, BigInteger>()
{
}

PublishedValues::PublishedValues(const BigInteger& t,
                                 const BigInteger& xt,
                                 const BigInteger& Pt,
                                 const BigInteger& mt)
    : boost::tuple<BigInteger, BigInteger, BigInteger, BigInteger>(t, xt, Pt, mt)
{
}

PublishedValues::PublishedValues(const PublishedValues& publishedValues)
    : boost::tuple<BigInteger, BigInteger, BigInteger, BigInteger>(publishedValues)
{
}

PublishedValues& PublishedValues::operator=(const PublishedValues& publishedValues)
{
    boost::tuple<BigInteger, BigInteger, BigInteger, BigInteger>::operator=(publishedValues);
    return *this;
}

const BigInteger& PublishedValues::getT() const
{
    return boost::get<0>(*this);
}

BigInteger& PublishedValues::getT()
{
    return boost::get<0>(*this);
}

const BigInteger& PublishedValues::getXt() const
{
    return boost::get<1>(*this);
}

BigInteger& PublishedValues::getXt()
{
    return boost::get<1>(*this);
}

const BigInteger& PublishedValues::getPt() const
{
    return boost::get<2>(*this);
}

BigInteger& PublishedValues::getPt()
{
    return boost::get<2>(*this);
}

const BigInteger& PublishedValues::getMt() const
{
    return boost::get<3>(*this);
}

BigInteger& PublishedValues::getMt()
{
    return boost::get<3>(*this);
}

bool operator<(const PublishedValues& left, const PublishedValues& right)
{
    return boost::get<0>(left) < boost::get<0>(right);
}
