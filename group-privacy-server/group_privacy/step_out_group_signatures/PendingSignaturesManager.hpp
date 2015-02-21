/**
 * @file PendingSignaturesManager.hpp
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

#ifndef PENDINGSIGNATURESMANAGER_HPP
#define	PENDINGSIGNATURESMANAGER_HPP

#include "../mpi/BigInteger.hpp"
#include "PendingSignature.hpp"

#include <string>
#include <vector>

class PendingSignaturesManager
{
public:
    unsigned int addPendingSignature(
        const unsigned int userIndex,
        const std::string& message,
        const BigInteger& t,
        const BigInteger& x);
    unsigned int addPendingSignature(const PendingSignature& pendingSignature);
    bool addUserToPendingSignature(
        const unsigned int signatureIndex,
        const unsigned int userIndex,
        const BigInteger& xt);
    bool closePendingSignature(const unsigned int signatureIndex, const unsigned int userIndex);
    const PendingSignature& getPendingSignature(const unsigned int signatureIndex) const;
    PendingSignature& getPendingSignature(const unsigned int signatureIndex);
private:
    std::vector<PendingSignature> pendingSignatures;
};

#endif // PENDINGSIGNATURESMANAGER_HPP
