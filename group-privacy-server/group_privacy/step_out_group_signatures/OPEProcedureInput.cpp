/**
 * @file OPEProcedureInput.cpp
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

#include "OPEProcedureInput.hpp"

OPEProcedureInputElement::OPEProcedureInputElement()
    : boost::tuple<BigInteger, BigInteger>()
{
}

OPEProcedureInputElement::OPEProcedureInputElement(const BigInteger& t, const BigInteger& x)
    : boost::tuple<BigInteger, BigInteger>(t, x)
{
}

OPEProcedureInputElement::OPEProcedureInputElement(const OPEProcedureInputElement& element)
    : boost::tuple<BigInteger, BigInteger>(element)
{
}

OPEProcedureInputElement& OPEProcedureInputElement::operator=(const OPEProcedureInputElement& element)
{
    boost::tuple<BigInteger, BigInteger>::operator=(element);
    return *this;
}

const BigInteger& OPEProcedureInputElement::t() const
{
    return boost::get<0>(*this);
}

BigInteger& OPEProcedureInputElement::t()
{
    return boost::get<0>(*this);
}

const BigInteger& OPEProcedureInputElement::x() const
{
    return boost::get<1>(*this);
}

BigInteger& OPEProcedureInputElement::x()
{
    return boost::get<1>(*this);
}

OPEProcedureInput::OPEProcedureInput()
    : boost::array<OPEProcedureInputElement, SGS::OPE_PROCEDURE_INPUT_SIZE>()
{
}

OPEProcedureInput::OPEProcedureInput(const OPEProcedureInput& array)
    : boost::array<OPEProcedureInputElement, SGS::OPE_PROCEDURE_INPUT_SIZE>(array)
{
}

OPEProcedureInput& OPEProcedureInput::operator=(const OPEProcedureInput& array)
{
        boost::array<OPEProcedureInputElement, SGS::OPE_PROCEDURE_INPUT_SIZE>::operator=(array);
        return *this;
}
