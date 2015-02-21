/**
 * @file PendingSignature.hpp
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

#ifndef PENDINGSIGNATURE_HPP
#define	PENDINGSIGNATURE_HPP

#include "../mpi/BigInteger.hpp"
#include "C.hpp"
#include "Delta.hpp"
#include "Sigma.hpp"
#include "ThetaPrim.hpp"

#include <boost/optional.hpp>

#include <map>
#include <string>

class PendingSignature
{
public:
    enum ESignatureStatus
    {
        SignatureStatusOpen,
        SignatureStatusClosed
    };

    PendingSignature(
        const unsigned int signatureInitializatorInit,
        const std::string& messageInit,
        const BigInteger& tInit,
        const BigInteger& xInit);
    PendingSignature(const PendingSignature& pendingSignature);
    PendingSignature& operator=(const PendingSignature& pendingSignature);
    bool addUser(const unsigned int userIndex, const BigInteger& xt);
    bool closeSignature(const unsigned int userIndex);
    bool finalizeSignature(const unsigned int userIndex, const ThetaPrimElement& thetaPrimElement);
    const std::string& getMessage() const;
    const std::map<unsigned int, ThetaPrimElement>& getSignersThetaPrimElements() const;
    const std::map<unsigned int, BigInteger>& getSignersXtValues() const;
    const BigInteger& getT() const;
    const BigInteger& getX() const;
    const Delta& getDelta() const;
    const ThetaPrim& getThetaPrim() const;
    const C& getC() const;
    const Sigma& getSigma() const;
    void setT(const BigInteger& t);
    void setX(const BigInteger& x);
    void setDelta(const Delta& delta);
    void setThetaPrim(const ThetaPrim& thetaPrim);
    void setC(const C& c);
    void setSigma(const Sigma& sigma);
private:
    ESignatureStatus signatureStatus;
    unsigned int signatureInitializator;
    std::string message;
    std::map<unsigned int, BigInteger> signersXtValues;
    std::map<unsigned int, ThetaPrimElement> signersThetaPrimElements;

    // step-out group signature:
    boost::optional<BigInteger> t;
    boost::optional<BigInteger> x;
    boost::optional<Delta> delta;
    boost::optional<ThetaPrim> thetaPrim;
    boost::optional<C> c;
    boost::optional<Sigma> sigma;
};

#endif // PENDINGSIGNATURE_HPP
