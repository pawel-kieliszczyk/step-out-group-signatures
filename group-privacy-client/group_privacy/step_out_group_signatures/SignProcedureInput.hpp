/**
 * @file SignProcedureInput.hpp
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

#ifndef SIGNPROCEDUREINPUT_HPP
#define	SIGNPROCEDUREINPUT_HPP

#include "../mpi/BigInteger.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/tuple/tuple.hpp>

#include <cstddef>
#include <string>

class SignProcedureInput : public boost::tuple<BigInteger, BigInteger, std::size_t, std::string>
{
    friend class boost::serialization::access;
public:
    SignProcedureInput();
    SignProcedureInput(const BigInteger& t,
                       const BigInteger& x,
                       const std::size_t d,
                       const std::string& h);
    SignProcedureInput(const SignProcedureInput& input);
    SignProcedureInput& operator=(const SignProcedureInput& input);
    const BigInteger& getT() const;
    BigInteger& getT();
    const BigInteger& getX() const;
    BigInteger& getX();
    const std::size_t& getD() const;
    std::size_t& getD();
    const std::string& getH() const;
    std::string& getH();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & getT();
        archive & getX();
        archive & getD();
        archive & getH();
    }
};

#endif // SIGNPROCEDUREINPUT_HPP
