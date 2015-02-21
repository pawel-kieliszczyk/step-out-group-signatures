/**
 * @file SExpFactory.cpp
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

#include "SExpressionFactory.hpp"

SExpression SExpressionFactory::createSExpression(const std::string& genString, const int autodetect)
{
    gcry_sexp_t sExp;
    gcry_error_t error = gcry_sexp_new(&sExp, genString.c_str(), genString.size(), autodetect);
    BOOST_ASSERT(!error);
    return SExpression(sExp);
}

SExpression SExpressionFactory::createHashSExpression(const unsigned char* hash, const unsigned int hashLength)
{
    gcry_sexp_t hashSExp;
    gcry_error_t error = gcry_sexp_build(&hashSExp,
                                         NULL,
                                         "(data (flags pkcs1) (hash sha256 %b))",
                                         hashLength,
                                         hash);
    BOOST_ASSERT(!error);
    return SExpression(hashSExp);
}

SExpression SExpressionFactory::createSignatureSExpression(const SExpression& hashSExpression, const IKey& privateKey)
{
    gcry_sexp_t signatureSExp;
    gcry_error_t error = gcry_pk_sign(&signatureSExp, hashSExpression.get(), privateKey.getSExpression().get());
    BOOST_ASSERT(!error);
    return SExpression(signatureSExp);
}

SExpression SExpressionFactory::findPrivateKeySExpression(const SExpression& keyPairSExpression)
{
    gcry_sexp_t privateKeySExp = gcry_sexp_find_token(keyPairSExpression.get(), "private-key", 0);
    BOOST_ASSERT(privateKeySExp);
    return SExpression(privateKeySExp);
}

SExpression SExpressionFactory::findPublicKeySExpression(const SExpression& keyPairSExpression)
{
    gcry_sexp_t privateKeySExp = gcry_sexp_find_token(keyPairSExpression.get(), "public-key", 0);
    BOOST_ASSERT(privateKeySExp);
    return SExpression(privateKeySExp);
}

SExpression SExpressionFactory::generateKeyPairSExpression(const SExpression& genSExpression)
{
    gcry_sexp_t keyPairSExp;
    gcry_error_t error = gcry_pk_genkey(&keyPairSExp, genSExpression.get());
    BOOST_ASSERT(!error);
    return SExpression(keyPairSExp);
}

bool SExpressionFactory::verifySignatureSExpression(const SExpression& hashSExpression,
                                                    const SExpression& signatureSExpression,
                                                    const IKey& publicKey)
{
    gcry_error_t invalidSignature = gcry_pk_verify(signatureSExpression.get(),
                                                   hashSExpression.get(),
                                                   publicKey.getSExpression().get());
    return (!invalidSignature);
}
