/**
 * @file InitializeSignatureInput.cpp
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

#include "InitializeSignatureInput.hpp"

InitializeSignatureInput::InitializeSignatureInput()
    : boost::tuple<unsigned int, std::string, BigInteger>()
{
}

InitializeSignatureInput::InitializeSignatureInput(
    const unsigned int userIndex,
    const std::string& message,
    const BigInteger& x)
    : boost::tuple<unsigned int, std::string, BigInteger>(userIndex, message, x)
{
}

InitializeSignatureInput::InitializeSignatureInput(const InitializeSignatureInput& input)
    : boost::tuple<unsigned int, std::string, BigInteger>(input)
{
}

InitializeSignatureInput InitializeSignatureInput::operator=(const InitializeSignatureInput& input)
{
    boost::tuple<unsigned int, std::string, BigInteger>::operator=(input);
    return *this;
}

const unsigned int& InitializeSignatureInput::getUserIndex() const
{
    return boost::get<0>(*this);
}

unsigned int& InitializeSignatureInput::getUserIndex()
{
    return boost::get<0>(*this);
}

const std::string& InitializeSignatureInput::getMessage() const
{
    return boost::get<1>(*this);
}

std::string& InitializeSignatureInput::getMessage()
{
    return boost::get<1>(*this);
}

const BigInteger& InitializeSignatureInput::getX() const
{
    return boost::get<2>(*this);
}

BigInteger& InitializeSignatureInput::getX()
{
    return boost::get<2>(*this);
}
