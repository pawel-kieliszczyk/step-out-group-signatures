/**
 * @file IKeyPair.hpp
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

#ifndef IKEYPAIR_HPP
#define	IKEYPAIR_HPP

#include "IKey.hpp"

#include <cstring>

class IKeyPair
{
public:
    virtual ~IKeyPair() {}
    void generate(const std::size_t keyLength)
    {
        generateImpl(keyLength);
    }
    const IKey& getPrivateKey() const
    {
        return getPrivateKeyImpl();
    }
    const IKey& getPublicKey() const
    {
        return getPublicKeyImpl();
    }
private:
    virtual void generateImpl(const std::size_t keyLength) = 0;
    virtual const IKey& getPrivateKeyImpl() const = 0;
    virtual const IKey& getPublicKeyImpl() const = 0;
};

#endif // IKEYPAIR_HPP
