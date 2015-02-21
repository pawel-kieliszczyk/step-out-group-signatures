/**
 * @file PendingSignature.cpp
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

#include "PendingSignature.hpp"

#include <boost/assert.hpp>

PendingSignature::PendingSignature(
    const unsigned int signatureInitializatorInit,
    const std::string& messageInit,
    const BigInteger& tInit,
    const BigInteger& xInit)
    : signatureStatus(SignatureStatusOpen),
      signatureInitializator(signatureInitializatorInit),
      message(messageInit),
      t(tInit),
      x(xInit)
{
}

PendingSignature::PendingSignature(const PendingSignature& pendingSignature)
    : signatureStatus(pendingSignature.signatureStatus),
      signatureInitializator(pendingSignature.signatureInitializator),
      message(pendingSignature.message),
      signersXtValues(pendingSignature.signersXtValues),
      t(pendingSignature.t),
      x(pendingSignature.x)
{
}

PendingSignature& PendingSignature::operator=(const PendingSignature& pendingSignature)
{
    signatureStatus = pendingSignature.signatureStatus;
    signatureInitializator = pendingSignature.signatureInitializator;
    message = pendingSignature.message;
    signersXtValues = pendingSignature.signersXtValues;
    t = pendingSignature.t;
    x = pendingSignature.x;
    return *this;
}

bool PendingSignature::addUser(const unsigned int userIndex, const BigInteger& xt)
{
    if(signatureStatus == SignatureStatusClosed)
        return false;
    signersXtValues[userIndex] = xt;
    return true;
}

bool PendingSignature::closeSignature(const unsigned int userIndex)
{
    if(userIndex == signatureInitializator)
    {
        signatureStatus = SignatureStatusClosed;
        return true;
    }
    return false;
}

bool PendingSignature::finalizeSignature(const unsigned int userIndex, const ThetaPrimElement& thetaPrimElement)
{
    if(signersXtValues.count(userIndex))
    {
        signersThetaPrimElements[userIndex] = thetaPrimElement;
        return true;
    }
    return false;
}

const std::string& PendingSignature::getMessage() const
{
    return message;
}

const std::map<unsigned int, ThetaPrimElement>& PendingSignature::getSignersThetaPrimElements() const
{
    return signersThetaPrimElements;
}

const std::map<unsigned int, BigInteger>& PendingSignature::getSignersXtValues() const
{
    return signersXtValues;
}

const BigInteger& PendingSignature::getT() const
{
    BOOST_ASSERT(t);
    return *t;
}

const BigInteger& PendingSignature::getX() const
{
    BOOST_ASSERT(x);
    return *x;
}

const Delta& PendingSignature::getDelta() const
{
    BOOST_ASSERT(delta);
    return *delta;
}

const ThetaPrim& PendingSignature::getThetaPrim() const
{
    BOOST_ASSERT(thetaPrim);
    return *thetaPrim;
}

const C& PendingSignature::getC() const
{
    BOOST_ASSERT(c);
    return *c;
}

const Sigma& PendingSignature::getSigma() const
{
    BOOST_ASSERT(sigma);
    return *sigma;
}

void PendingSignature::setT(const BigInteger& t)
{
    this->t = t;
}

void PendingSignature::setX(const BigInteger& x)
{
    this->x = x;
}

void PendingSignature::setDelta(const Delta& delta)
{
    this->delta = delta;
}

void PendingSignature::setThetaPrim(const ThetaPrim& thetaPrim)
{
    this->thetaPrim = thetaPrim;
}

void PendingSignature::setC(const C& c)
{
    this->c = c;
}

void PendingSignature::setSigma(const Sigma& sigma)
{
    this->sigma = sigma;
}
