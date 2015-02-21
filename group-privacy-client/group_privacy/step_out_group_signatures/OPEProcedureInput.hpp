/**
 * @file OPEProcedureInput.hpp
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

#ifndef OPEPROCEDUREINPUT_HPP
#define	OPEPROCEDUREINPUT_HPP

#include "../mpi/BigInteger.hpp"
#include "StepOutGroupSignaturesConstants.hpp"

#include <boost/array.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/access.hpp>
#include <boost/tuple/tuple.hpp>

class OPEProcedureInputElement : public boost::tuple<BigInteger, BigInteger>
{
    friend class boost::serialization::access;
public:
    OPEProcedureInputElement();
    OPEProcedureInputElement(const BigInteger& t, const BigInteger& x);
    OPEProcedureInputElement(const OPEProcedureInputElement& element);
    OPEProcedureInputElement& operator=(const OPEProcedureInputElement& element);
    const BigInteger& t() const;
    BigInteger& t();
    const BigInteger& x() const;
    BigInteger& x();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & t();
        archive & x();
    }
};

class OPEProcedureInput : public boost::array<OPEProcedureInputElement, SGS::OPE_PROCEDURE_INPUT_SIZE>
{
    friend class boost::serialization::access;
public:
    OPEProcedureInput();
    OPEProcedureInput(const OPEProcedureInput& array);
    OPEProcedureInput& operator=(const OPEProcedureInput& array);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & dynamic_cast<boost::array<OPEProcedureInputElement, SGS::OPE_PROCEDURE_INPUT_SIZE>&>(*this);
    }
};

#endif // OPEPROCEDUREINPUT_HPP
