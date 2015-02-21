/**
 * @file UserPublicKey.hpp
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

#ifndef USERPUBLICKEY_HPP
#define	USERPUBLICKEY_HPP

#include "../polynomial_in_the_exponent/PolynomialInTheExponent.hpp"
#include "../step_out_group_signatures/StepOutGroupSignaturesConstants.hpp"

#include <boost/serialization/access.hpp>

class UserPublicKey
{
    friend class boost::serialization::access;
public:
    UserPublicKey();
    UserPublicKey(const PolynomialInTheExponent<SGS::QM_POLYNOMIAL_DEGREE>& gQmInit);
    UserPublicKey(const UserPublicKey& userPublicKey);
    UserPublicKey& operator=(const UserPublicKey& userPublicKey);
    const PolynomialInTheExponent<SGS::QM_POLYNOMIAL_DEGREE>& getQm() const;
    void setQm(const PolynomialInTheExponent<SGS::QM_POLYNOMIAL_DEGREE>& gQmInit);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & gQm;
    }

    PolynomialInTheExponent<SGS::QM_POLYNOMIAL_DEGREE> gQm;
};

#endif // USERPUBLICKEY_HPP
