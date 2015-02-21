/**
 * @file RSAKeyPair.hpp
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

#ifndef RSAKEYPAIR_HPP
#define	RSAKEYPAIR_HPP

#include "../s_expression/SExpression.hpp"
#include "IKey.hpp"
#include "IKeyPair.hpp"

#include <boost/shared_ptr.hpp>

#include <cstring>

class RSAKeyPair : public IKeyPair
{
public:
    RSAKeyPair();
    RSAKeyPair(const std::size_t keyLength);
private:
    void exportKeys(const SExpression& keyPairSExpression);
    void exportPrivateKey(const SExpression& keyPairSExpression);
    void exportPublicKey(const SExpression& keyPairSExpression);
    void generateImpl(const std::size_t keyLength);
    const IKey& getPrivateKeyImpl() const;
    const IKey& getPublicKeyImpl() const;
    SExpression prepareGeneratingSExpression(const std::size_t keyLength);

    boost::shared_ptr<IKey>   privateKey;   /**< Private RSA key. */
    boost::shared_ptr<IKey>   publicKey;    /**< Public RSA key. */
};

#endif // RSAKEYPAIR_HPP
