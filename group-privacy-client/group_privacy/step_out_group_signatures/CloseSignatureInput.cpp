/**
 * @file CloseSignatureInput.cpp
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

#include "CloseSignatureInput.hpp"

CloseSignatureInput::CloseSignatureInput()
    : boost::tuple<unsigned int, unsigned int>()
{
}

CloseSignatureInput::CloseSignatureInput(const unsigned int userIndex, const unsigned int signatureIndex)
    : boost::tuple<unsigned int, unsigned int>(userIndex, signatureIndex)
{
}

CloseSignatureInput::CloseSignatureInput(const CloseSignatureInput& input)
    : boost::tuple<unsigned int, unsigned int>(input)
{
}

CloseSignatureInput CloseSignatureInput::operator=(const CloseSignatureInput& input)
{
    boost::tuple<unsigned int, unsigned int>::operator=(input);
    return *this;
}

const unsigned int& CloseSignatureInput::getUserIndex() const
{
    return boost::get<0>(*this);
}

unsigned int& CloseSignatureInput::getUserIndex()
{
    return boost::get<0>(*this);
}

const unsigned int& CloseSignatureInput::getSignatureIndex() const
{
    return boost::get<1>(*this);
}

unsigned int& CloseSignatureInput::getSignatureIndex()
{
    return boost::get<1>(*this);
}
