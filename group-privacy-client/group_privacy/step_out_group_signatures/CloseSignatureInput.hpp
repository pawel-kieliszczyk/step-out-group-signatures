/**
 * @file CloseSignatureInput.hpp
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

#ifndef CLOSESIGNATUREINPUT_HPP
#define	CLOSESIGNATUREINPUT_HPP

#include <boost/serialization/access.hpp>
#include <boost/tuple/tuple.hpp>

class CloseSignatureInput : public boost::tuple<unsigned int, unsigned int>
{
    friend class boost::serialization::access;
public:
    CloseSignatureInput();
    CloseSignatureInput(const unsigned int userIndex, const unsigned int signatureIndex);
    CloseSignatureInput(const CloseSignatureInput& input);
    CloseSignatureInput operator=(const CloseSignatureInput& input);
    const unsigned int& getUserIndex() const;
    unsigned int& getUserIndex();
    const unsigned int& getSignatureIndex() const;
    unsigned int& getSignatureIndex();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & getUserIndex();
        archive & getSignatureIndex();
    }
};

#endif // CLOSESIGNATUREINPUT_HPP
