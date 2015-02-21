/**
 * @file Delta.cpp
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

#include "Delta.hpp"

DeltaElement::DeltaElement() : boost::tuple<BigInteger, BigInteger>()
{
}

DeltaElement::DeltaElement(const BigInteger& i, const BigInteger& grLti)
    : boost::tuple<BigInteger, BigInteger>(i, grLti)
{
}

DeltaElement::DeltaElement(const DeltaElement& element)
    : boost::tuple<BigInteger, BigInteger>(element)
{
}

DeltaElement& DeltaElement::operator=(const DeltaElement& element)
{
    boost::tuple<BigInteger, BigInteger>::operator=(element);
    return *this;
}

const BigInteger& DeltaElement::i() const
{
    return boost::get<0>(*this);
}

BigInteger& DeltaElement::i()
{
    return boost::get<0>(*this);
}

const BigInteger& DeltaElement::grLti() const
{
    return boost::get<1>(*this);
}

BigInteger& DeltaElement::grLti()
{
    return boost::get<1>(*this);
}

Delta::Delta() : std::vector<DeltaElement>()
{
}

Delta::Delta(const Delta& delta) : std::vector<DeltaElement>(delta)
{
}

Delta& Delta::operator=(const Delta& delta)
{
    std::vector<DeltaElement>::operator=(delta);
    return *this;
}
