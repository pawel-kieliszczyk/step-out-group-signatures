/**
 * @file ThetaPrim.cpp
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

#include "ThetaPrim.hpp"

ThetaPrimElement::ThetaPrimElement()
    : boost::tuple<BigInteger, BigInteger, BigInteger>()
{
}

ThetaPrimElement::ThetaPrimElement(const BigInteger& xt, const BigInteger& grPt, const BigInteger& gQtrSt)
    : boost::tuple<BigInteger, BigInteger, BigInteger>(xt, grPt, gQtrSt)
{
}

ThetaPrimElement::ThetaPrimElement(const ThetaPrimElement& element)
    : boost::tuple<BigInteger, BigInteger, BigInteger>(element)
{
}

ThetaPrimElement& ThetaPrimElement::operator=(const ThetaPrimElement& element)
{
    boost::tuple<BigInteger, BigInteger, BigInteger>::operator=(element);
    return *this;
}

const BigInteger& ThetaPrimElement::xt() const
{
    return boost::get<0>(*this);
}

BigInteger& ThetaPrimElement::xt()
{
    return boost::get<0>(*this);
}

const BigInteger& ThetaPrimElement::grPt() const
{
    return boost::get<1>(*this);
}

BigInteger& ThetaPrimElement::grPt()
{
    return boost::get<1>(*this);
}

const BigInteger& ThetaPrimElement::gQtrSt() const
{
    return boost::get<2>(*this);
}

BigInteger& ThetaPrimElement::gQtrSt()
{
    return boost::get<2>(*this);
}

ThetaPrim::ThetaPrim() : std::vector<ThetaPrimElement>()
{
}

ThetaPrim::ThetaPrim(const ThetaPrim& thetaPrim)
    : std::vector<ThetaPrimElement>(thetaPrim)
{
}

ThetaPrim& ThetaPrim::operator=(const ThetaPrim& thetaPrim)
{
    std::vector<ThetaPrimElement>::operator=(thetaPrim);
    return *this;
}
