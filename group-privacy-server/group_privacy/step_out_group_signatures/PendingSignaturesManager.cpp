/**
 * @file PendingSignaturesManager.cpp
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

#include "PendingSignaturesManager.hpp"

unsigned int PendingSignaturesManager::addPendingSignature(
    const unsigned int userIndex,
    const std::string& message,
    const BigInteger& t,
    const BigInteger& x)
{
    return addPendingSignature(PendingSignature(userIndex, message, t, x));
}

unsigned int PendingSignaturesManager::addPendingSignature(const PendingSignature& pendingSignature)
{
    pendingSignatures.push_back(pendingSignature);
    return (pendingSignatures.size() - 1);
}

bool PendingSignaturesManager::addUserToPendingSignature(
    const unsigned int signatureIndex,
    const unsigned int userIndex,
    const BigInteger& xt)
{
    BOOST_ASSERT(signatureIndex < pendingSignatures.size());
    return pendingSignatures[signatureIndex].addUser(userIndex, xt);
}

bool PendingSignaturesManager::closePendingSignature(const unsigned int signatureIndex, const unsigned int userIndex)
{
    BOOST_ASSERT(signatureIndex < pendingSignatures.size());
    return pendingSignatures[signatureIndex].closeSignature(userIndex);
}

const PendingSignature& PendingSignaturesManager::getPendingSignature(const unsigned int signatureIndex) const
{
    BOOST_ASSERT(signatureIndex < pendingSignatures.size());
    return pendingSignatures[signatureIndex];
}

PendingSignature& PendingSignaturesManager::getPendingSignature(const unsigned int signatureIndex)
{
    BOOST_ASSERT(signatureIndex < pendingSignatures.size());
    return pendingSignatures[signatureIndex];
}
