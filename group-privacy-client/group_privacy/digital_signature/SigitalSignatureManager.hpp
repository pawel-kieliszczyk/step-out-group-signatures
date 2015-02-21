/**
 * @file DigitalSignatureManager.hpp
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
 * The file contains DigitalSignatureManager class which
 * creates and verifies digital signatures.
 */

#ifndef DIGITALSIGNATUREMANAGER_HPP
#define	DIGITALSIGNATUREMANAGER_HPP

#include "../key/IKey.hpp"
#include "../s_expression/SExpression.hpp"
#include "../s_expression/SExpressionFactory.hpp"
#include "DigitalSignature.hpp"

#include <gcrypt.h>

/**
 * DigitalSignature class.
 *
 * It can create and verify digital signatures.
 */
class DigitalSignatureManager
{
public:
    /**
     * Signs a given message using a given private key.
     *
     * @param hash Hash code of the message to be signed.
     * @param hashLength Lenght of the given hash code.
     * @param privateKey Private key to be used to sign the message.
     *
     * @return \c DigitalSignature object containing the created signature.
     */
    static DigitalSignature sign(const unsigned char* hash, const unsigned int hashLength, const IKey& privateKey)
    {
        SExpression hashSExp = SExpressionFactory::createHashSExpression(hash, hashLength);
        SExpression signatureSExp = SExpressionFactory::createSignatureSExpression(hashSExp, privateKey);
        return DigitalSignature(signatureSExp);
    }

    /**
     * Verifies if a given siganture is a valid signature of a given message.
     *
     * @param hash Hash code of the message.
     * @param hashLength Lenght of the given hash code.
     * @param digitalSignature Digital signature to be verified.
     * @param publicKey Public key that is to be used for verification.
     *
     * @return True if a given signature is a valid signature of the given message.
     */
    static bool verify(const unsigned char* hash,
                       const unsigned int hashLength,
                       const DigitalSignature& digitalSignature,
                       const IKey& publicKey)
    {
        SExpression hashSExp = SExpressionFactory::createHashSExpression(hash, hashLength);
        return SExpressionFactory::verifySignatureSExpression(hashSExp, digitalSignature.getSExpression(), publicKey);
    }
};

#endif // DIGITALSIGNATUREMANAGER_HPP
