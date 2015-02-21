/**
 * @file C.cpp
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

#include "C.hpp"

C::C() : boost::tuple<BigInteger, BigInteger, BigInteger>()
{
}

C::C(const BigInteger& gr, const BigInteger& rSt, const BigInteger& grLtx)
    : boost::tuple<BigInteger, BigInteger, BigInteger>(gr, rSt, grLtx)
{
}

C::C(const C& c) : boost::tuple<BigInteger, BigInteger, BigInteger>(c)
{
}

C& C::operator=(const C& c)
{
    boost::tuple<BigInteger, BigInteger, BigInteger>::operator=(c);
    return *this;
}

const BigInteger& C::gr() const
{
    return boost::get<0>(*this);
}

BigInteger& C::gr()
{
    return boost::get<0>(*this);
}

const BigInteger& C::rSt() const
{
    return boost::get<1>(*this);
}

BigInteger& C::rSt()
{
    return boost::get<1>(*this);
}

const BigInteger& C::grLtx() const
{
    return boost::get<2>(*this);
}

BigInteger& C::grLtx()
{
    return boost::get<2>(*this);
}
