/**
 * @file SigProcedureInput.hpp
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

#include "SignProcedureInput.hpp"

SignProcedureInput::SignProcedureInput() : boost::tuple<BigInteger, BigInteger, std::size_t, std::string>()
{
}

SignProcedureInput::SignProcedureInput(const BigInteger& t,
                                       const BigInteger& x,
                                       const std::size_t d,
                                       const std::string& h)
    : boost::tuple<BigInteger, BigInteger, std::size_t, std::string>(t, x, d, h)
{
}

SignProcedureInput::SignProcedureInput(const SignProcedureInput& input)
    : boost::tuple<BigInteger, BigInteger, std::size_t, std::string>(input)
{
}

SignProcedureInput& SignProcedureInput::operator=(const SignProcedureInput& input)
{
    boost::tuple<BigInteger, BigInteger, std::size_t, std::string>::operator=(input);
    return *this;
}

const BigInteger& SignProcedureInput::getT() const
{
    return boost::get<0>(*this);
}

BigInteger& SignProcedureInput::getT()
{
    return boost::get<0>(*this);
}

const BigInteger& SignProcedureInput::getX() const
{
    return boost::get<1>(*this);
}

BigInteger& SignProcedureInput::getX()
{
    return boost::get<1>(*this);
}

const std::size_t& SignProcedureInput::getD() const
{
    return boost::get<2>(*this);
}

std::size_t& SignProcedureInput::getD()
{
    return boost::get<2>(*this);
}

const std::string& SignProcedureInput::getH() const
{
    return boost::get<3>(*this);
}

std::string& SignProcedureInput::getH()
{
    return boost::get<3>(*this);
}
