/**
 * @file RSAKeyPair.cpp
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

#include "RSAKeyPair.hpp"

#include "../s_expression/SExpressionFactory.hpp"
#include "RSAKey.hpp"

#include <boost/lexical_cast.hpp>

#include <string>

RSAKeyPair::RSAKeyPair()
    : privateKey(),
      publicKey()
{
}

RSAKeyPair::RSAKeyPair(const std::size_t keyLength)
    : privateKey(),
      publicKey()
{
    generateImpl(keyLength);
}

void RSAKeyPair::exportKeys(const SExpression& keyPairSExpression)
{
    exportPrivateKey(keyPairSExpression);
    exportPublicKey(keyPairSExpression);
}

void RSAKeyPair::exportPrivateKey(const SExpression& keyPairSExpression)
{
    privateKey.reset(new RSAKey(SExpressionFactory::findPrivateKeySExpression(keyPairSExpression)));
}

void RSAKeyPair::exportPublicKey(const SExpression& keyPairSExpression)
{
    publicKey.reset(new RSAKey(SExpressionFactory::findPublicKeySExpression(keyPairSExpression)));
}

void RSAKeyPair::generateImpl(const std::size_t keyLength)
{
    SExpression genSExpression = prepareGeneratingSExpression(keyLength);
    SExpression keyPairSExpression = SExpressionFactory::generateKeyPairSExpression(genSExpression);
    exportKeys(keyPairSExpression);
}

const IKey& RSAKeyPair::getPrivateKeyImpl() const
{
    return *privateKey;
}

const IKey& RSAKeyPair::getPublicKeyImpl() const
{
    return *publicKey;
}

SExpression RSAKeyPair::prepareGeneratingSExpression(const std::size_t keyLength)
{
    const std::string genString = "(genkey (rsa (nbits 4:" + boost::lexical_cast<std::string>(keyLength) + ")))";
    const int AUTODETECT = 1;
    return SExpressionFactory::createSExpression(genString, AUTODETECT);
}
