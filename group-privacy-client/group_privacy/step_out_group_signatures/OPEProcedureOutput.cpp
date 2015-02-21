/**
 * @file OPEProcedureOutput.cpp
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

#include "OPEProcedureOutput.hpp"

OPEProcedureOutputElement::OPEProcedureOutputElement()
    : boost::tuple<BigInteger, BigInteger>()
{
}

OPEProcedureOutputElement::OPEProcedureOutputElement(const BigInteger& p, const BigInteger& q)
    : boost::tuple<BigInteger, BigInteger>(p, q)
{
}

OPEProcedureOutputElement::OPEProcedureOutputElement(const OPEProcedureOutputElement& element)
    : boost::tuple<BigInteger, BigInteger>(element)
{
}

OPEProcedureOutputElement& OPEProcedureOutputElement::operator=(const OPEProcedureOutputElement& element)
{
    boost::tuple<BigInteger, BigInteger>::operator=(element);
    return *this;
}

const BigInteger OPEProcedureOutputElement::p() const
{
    return boost::get<0>(*this);
}

BigInteger& OPEProcedureOutputElement::p()
{
    return boost::get<0>(*this);
}

const BigInteger& OPEProcedureOutputElement::q() const
{
    return boost::get<1>(*this);
}

BigInteger& OPEProcedureOutputElement::q()
{
    return boost::get<1>(*this);
}

OPEProcedureOutput::OPEProcedureOutput()
    : boost::array<OPEProcedureOutputElement, SGS::OPE_PROCEDURE_OUTPUT_SIZE>()
{
}

OPEProcedureOutput::OPEProcedureOutput(const OPEProcedureOutput& array)
    : boost::array<OPEProcedureOutputElement, SGS::OPE_PROCEDURE_OUTPUT_SIZE>(array)
{
}

OPEProcedureOutput& OPEProcedureOutput::operator=(const OPEProcedureOutput& array)
{
        boost::array<OPEProcedureOutputElement, SGS::OPE_PROCEDURE_OUTPUT_SIZE>::operator=(array);
        return *this;
}
