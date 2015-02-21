/**
 * @file FinalizeSignatureInput.cpp
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

#include "FinalizeSignatureInput.hpp"

FinalizeSignatureInput::FinalizeSignatureInput()
    : boost::tuple<BigInteger, BigInteger, BigInteger>()
{
}

FinalizeSignatureInput::FinalizeSignatureInput(const BigInteger& t, const BigInteger& gr, const BigInteger& rSt)
    : boost::tuple<BigInteger, BigInteger, BigInteger>(t, gr, rSt)
{
}

FinalizeSignatureInput::FinalizeSignatureInput(const FinalizeSignatureInput& input)
    : boost::tuple<BigInteger, BigInteger, BigInteger>(input)
{
}

FinalizeSignatureInput FinalizeSignatureInput::operator=(const FinalizeSignatureInput& input)
{
    boost::tuple<BigInteger, BigInteger, BigInteger>::operator=(input);
    return *this;
}

const BigInteger& FinalizeSignatureInput::getT() const
{
    return boost::get<0>(*this);
}

BigInteger& FinalizeSignatureInput::getT()
{
    return boost::get<0>(*this);
}

const BigInteger& FinalizeSignatureInput::getGr() const
{
    return boost::get<1>(*this);
}

BigInteger& FinalizeSignatureInput::getGr()
{
    return boost::get<1>(*this);
}

const BigInteger& FinalizeSignatureInput::getRSt() const
{
    return boost::get<2>(*this);
}

BigInteger& FinalizeSignatureInput::getRSt()
{
    return boost::get<2>(*this);
}
