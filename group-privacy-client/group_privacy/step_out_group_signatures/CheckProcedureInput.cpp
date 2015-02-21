/**
 * @file CheckProcedureInput.cpp
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

#include "CheckProcedureInput.hpp"

CheckProcedureInput::CheckProcedureInput() : boost::tuple<unsigned int, BigInteger>()
{
}

CheckProcedureInput::CheckProcedureInput(const unsigned int userIndex, const BigInteger& t)
    : boost::tuple<unsigned int, BigInteger>(userIndex, t)
{
}

CheckProcedureInput::CheckProcedureInput(const CheckProcedureInput& input)
    : boost::tuple<unsigned int, BigInteger>(input)
{
}

CheckProcedureInput& CheckProcedureInput::operator=(const CheckProcedureInput& input)
{
    boost::tuple<unsigned int, BigInteger>::operator=(input);
    return *this;
}

const unsigned int& CheckProcedureInput::getUserIndex() const
{
    return boost::get<0>(*this);
}

unsigned int& CheckProcedureInput::getUserIndex()
{
    return boost::get<0>(*this);
}

const BigInteger& CheckProcedureInput::getT() const
{
    return boost::get<1>(*this);
}

BigInteger& CheckProcedureInput::getT()
{
    return boost::get<1>(*this);
}
