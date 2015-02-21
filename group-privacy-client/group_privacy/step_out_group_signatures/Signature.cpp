/**
 * @file Signature.cpp
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

#include "Signature.hpp"

Signature::Signature() : boost::tuple<BigInteger, BigInteger, Delta, ThetaPrim, C, Sigma>()
{
}

Signature::Signature(const Signature& signature)
    : boost::tuple<BigInteger, BigInteger, Delta, ThetaPrim, C, Sigma>(signature)
{
}

Signature::Signature(const BigInteger&   t,
                     const BigInteger&   x,
                     const Delta&        delta,
                     const ThetaPrim     thetaPrim,
                     const C&            c,
                     const Sigma&        sigma)
    : boost::tuple<BigInteger, BigInteger, Delta, ThetaPrim, C, Sigma>(t, x, delta, thetaPrim, c, sigma)
{
}

Signature& Signature::operator=(const Signature& signature)
{
    boost::tuple<BigInteger, BigInteger, Delta, ThetaPrim, C, Sigma>::operator=(signature);
    return *this;
}

const BigInteger& Signature::getT() const
{
    return boost::get<0>(*this);
}

BigInteger& Signature::getT()
{
    return boost::get<0>(*this);
}

const BigInteger& Signature::getX() const
{
    return boost::get<1>(*this);
}

BigInteger& Signature::getX()
{
    return boost::get<1>(*this);
}

const Delta& Signature::getDelta() const
{
    return boost::get<2>(*this);
}

Delta& Signature::getDelta()
{
    return boost::get<2>(*this);
}

const ThetaPrim& Signature::getThetaPrim() const
{
    return boost::get<3>(*this);
}

ThetaPrim& Signature::getThetaPrim()
{
    return boost::get<3>(*this);
}

const C& Signature::getC() const
{
    return boost::get<4>(*this);
}

C& Signature::getC()
{
    return boost::get<4>(*this);
}

const Sigma& Signature::getSigma() const
{
    return boost::get<5>(*this);
}

Sigma& Signature::getSigma()
{
    return boost::get<5>(*this);
}
