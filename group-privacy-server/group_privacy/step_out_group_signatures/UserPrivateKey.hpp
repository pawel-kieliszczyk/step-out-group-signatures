/**
 * @file UserPrivateKey.hpp
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

#ifndef USERPRIVATEKEY_HPP
#define	USERPRIVATEKEY_HPP

#include "../polynomial/Polynomial.hpp"
#include "../polynomial_in_the_exponent/PolynomialInTheExponent.hpp"
#include "../step_out_group_signatures/StepOutGroupSignaturesConstants.hpp"

#include <boost/serialization/access.hpp>

class UserPrivateKey
{
    friend class boost::serialization::access;
public:
    UserPrivateKey();
    UserPrivateKey(const UserPrivateKey& userPrivateKey);
    UserPrivateKey& operator=(const UserPrivateKey& userPrivateKey);
    const Polynomial<SGS::M_POLYNOMIAL_DEGREE>& getM() const;
    Polynomial<SGS::M_POLYNOMIAL_DEGREE>& getM();
    const Polynomial<SGS::P_POLYNOMIAL_DEGREE>& getP() const;
    Polynomial<SGS::P_POLYNOMIAL_DEGREE>& getP();
    const PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& getQ() const;
    PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& getQ();
    const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& getX() const;
    Polynomial<SGS::X_POLYNOMIAL_DEGREE>& getX();
    void setM(const Polynomial<SGS::M_POLYNOMIAL_DEGREE>& mPolynomialInit);
    void setP(const Polynomial<SGS::P_POLYNOMIAL_DEGREE>& pPolynomialInit);
    void setQ(const PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& qPolynomialInit);
    void setX(const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& xPolynomialInit);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & mPolynomial;
        archive & pPolynomial;
        archive & qPolynomial;
        archive & xPolynomial;
    }

    Polynomial<SGS::M_POLYNOMIAL_DEGREE>                mPolynomial;
    Polynomial<SGS::P_POLYNOMIAL_DEGREE>                pPolynomial;
    PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>   qPolynomial;
    Polynomial<SGS::X_POLYNOMIAL_DEGREE>                xPolynomial;
};

#endif // USERPRIVATEKEY_HPP
