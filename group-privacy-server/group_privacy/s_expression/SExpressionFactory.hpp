/**
 * @file SExpressionFactory.hpp
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
 *
 * The file contains SExpression Factory which creates
 * instances of SExpression class.
 */

#ifndef SEXPRESSIONFACTORY_HPP
#define	SEXPRESSIONFACTORY_HPP

#include "../key/IKey.hpp"
#include "SExpression.hpp"

#include <gcrypt.h>
#include <gpg-error.h>

#include <boost/assert.hpp>

/**
 * SExpressionFactory class.
 *
 * Creates instances of SExpression class.
 */
class SExpressionFactory
{
public:
    /**
     * Creates s-expression based on a given \c std::string object.
     *
     * @param genString Generating string.
     * @param autodetect Specifies whether end of the string should be automatically detected.
     *
     * @return S-expression created from the given string.
     */
    static SExpression createSExpression(const std::string& genString, const int autodetect);

    /**
     * Creates s-expression based on a given hash code.
     *
     * @param hash Hash code.
     * @param hashLength Length of the hash code.
     *
     * @return S-expression created from the given hash code.
     */
    static SExpression createHashSExpression(const unsigned char* hash, const unsigned int hashLength);

    /**
     * Creates s-expression which is a digital signature of a given hashed message.
     *
     * @param hashSExpression Hash code to be signed.
     * @param privateKey Private key that is to be used in signing.
     *
     * @return S-expression containing the created signature.
     */
    static SExpression createSignatureSExpression(const SExpression& hashSExpression, const IKey& privateKey);

    /**
     * Finds a private key in a given s-expression.
     *
     * @param keyPairSExpression S-expression containing a kay pair.
     *
     * @return S-expression contining a private key extracted from the given key pair.
     */
    static SExpression findPrivateKeySExpression(const SExpression& keyPairSExpression);

    /**
     * Finds a public key in a given s-expression.
     *
     * @param keyPairSExpression S-expression containing a kay pair.
     *
     * @return S-expression contining a public key extracted from the given key pair.
     */
    static SExpression findPublicKeySExpression(const SExpression& keyPairSExpression);

    /**
     * Generates an s-expression containg a key pair based on a given s-expression.
     *
     * @param genSExpression Generator of the key pair.
     *
     * @return S-expression containing the created key pair.
     */
    static SExpression generateKeyPairSExpression(const SExpression& genSExpression);

    /**
     * Verifies a digital signature stored as a s-expression.
     *
     * @param hashSExpression Hash of a message.
     * @param signatureSExpression S-expression containing the signature that is to be checked.
     * @param publicKey Cryptographic public key.
     *
     * @return True if a signature is valud. False otherwise.
     */
    static bool verifySignatureSExpression(const SExpression& hashSExpression,
                                           const SExpression& signatureSExpression,
                                           const IKey& publicKey);
};

#endif // SEXPRESSIONFACTORY_HPP
