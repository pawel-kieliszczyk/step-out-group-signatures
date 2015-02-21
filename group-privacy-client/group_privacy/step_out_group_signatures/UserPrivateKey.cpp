/**
 * @file UserPrivateKey.cpp
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

#include "UserPrivateKey.hpp"

UserPrivateKey::UserPrivateKey()
    : pPolynomial(),
      qPolynomial(),
      xPolynomial()
{
}

UserPrivateKey::UserPrivateKey(const UserPrivateKey& userPrivateKey)
    : pPolynomial(userPrivateKey.pPolynomial),
      qPolynomial(userPrivateKey.qPolynomial),
      xPolynomial(userPrivateKey.xPolynomial)
{
}

UserPrivateKey& UserPrivateKey::operator=(const UserPrivateKey& userPrivateKey)
{
    pPolynomial = userPrivateKey.pPolynomial;
    qPolynomial = userPrivateKey.qPolynomial;
    xPolynomial = userPrivateKey.xPolynomial;
    return *this;
}

const Polynomial<SGS::M_POLYNOMIAL_DEGREE>& UserPrivateKey::getM() const
{
    return mPolynomial;
}
Polynomial<SGS::M_POLYNOMIAL_DEGREE>& UserPrivateKey::getM()
{
    return mPolynomial;
}

const Polynomial<SGS::P_POLYNOMIAL_DEGREE>& UserPrivateKey::getP() const
{
    return pPolynomial;
}

Polynomial<SGS::P_POLYNOMIAL_DEGREE>& UserPrivateKey::getP()
{
    return pPolynomial;
}

const PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& UserPrivateKey::getQ() const
{
    return qPolynomial;
}

PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& UserPrivateKey::getQ()
{
    return qPolynomial;
}

const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& UserPrivateKey::getX() const
{
    return xPolynomial;
}

Polynomial<SGS::X_POLYNOMIAL_DEGREE>& UserPrivateKey::getX()
{
    return xPolynomial;
}

void UserPrivateKey::setM(const Polynomial<SGS::M_POLYNOMIAL_DEGREE>& mPolynomialInit)
{
    mPolynomial = mPolynomialInit;
}

void UserPrivateKey::setP(const Polynomial<SGS::P_POLYNOMIAL_DEGREE>& pPolynomialInit)
{
    pPolynomial = pPolynomialInit;
}

void UserPrivateKey::setQ(const PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& qPolynomialInit)
{
    qPolynomial = qPolynomialInit;
}

void UserPrivateKey::setX(const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& xPolynomialInit)
{
    xPolynomial = xPolynomialInit;
}

