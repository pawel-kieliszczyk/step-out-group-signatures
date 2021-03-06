/**
 * @file Theta.cpp
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

#include "Theta.hpp"

ThetaElement::ThetaElement()
    : boost::tuple<BigInteger, BigInteger>()
{
}

ThetaElement::ThetaElement(const BigInteger& first, const BigInteger& second)
    : boost::tuple<BigInteger, BigInteger>(first, second)
{
}

ThetaElement::ThetaElement(const ThetaElement& element)
    : boost::tuple<BigInteger, BigInteger>(element)
{
}

ThetaElement& ThetaElement::operator=(const ThetaElement& element)
{
    boost::tuple<BigInteger, BigInteger>::operator=(element);
    return *this;
}

bool operator==(const ThetaElement& left, const ThetaElement& right)
{
    return (boost::get<0>(left) == boost::get<0>(right) && boost::get<1>(left) == boost::get<1>(right));
}

Theta::Theta() : std::vector<ThetaElement>()
{
}

Theta::Theta(const Theta& theta)
    : std::vector<ThetaElement>(theta)
{
}

Theta& Theta::operator=(const Theta& theta)
{
    std::vector<ThetaElement>::operator=(theta);
    return *this;
}
