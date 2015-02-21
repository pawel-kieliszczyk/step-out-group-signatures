/**
 * @file InitializeSignatureInput.hpp
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

#ifndef INITIALIZESIGNATUREINPUT_HPP
#define	INITIALIZESIGNATUREINPUT_HPP

#include "../mpi/BigInteger.hpp"

#include <boost/serialization/access.hpp>
#include <boost/tuple/tuple.hpp>

#include <string>

class InitializeSignatureInput : public boost::tuple<unsigned int, std::string, BigInteger>
{
    friend class boost::serialization::access;
public:
    InitializeSignatureInput();
    InitializeSignatureInput(const unsigned int userIndex, const std::string& message, const BigInteger& x);
    InitializeSignatureInput(const InitializeSignatureInput& input);
    InitializeSignatureInput operator=(const InitializeSignatureInput& input);
    const unsigned int& getUserIndex() const;
    unsigned int& getUserIndex();
    const std::string& getMessage() const;
    std::string& getMessage();
    const BigInteger& getX() const;
    BigInteger& getX();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & getUserIndex();
        archive & getMessage();
        archive & getX();
    }
};

#endif // INITIALIZESIGNATUREINPUT_HPP
