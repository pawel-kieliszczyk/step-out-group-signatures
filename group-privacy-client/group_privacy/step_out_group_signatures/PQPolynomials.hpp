/**
 * @file PQPolynomials.hpp
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

#ifndef PQPOLYNOMIALS_HPP
#define	PQPOLYNOMIALS_HPP

#include "../polynomial/Polynomial.hpp"
#include "../polynomial_in_the_exponent/PolynomialInTheExponent.hpp"
#include "StepOutGroupSignaturesConstants.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/tuple/tuple.hpp>

class PQPolynomials : public boost::tuple<Polynomial<SGS::P_POLYNOMIAL_DEGREE>,
                                          PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE> >
{
    friend class boost::serialization::access;
public:
    PQPolynomials();
    PQPolynomials(const Polynomial<SGS::P_POLYNOMIAL_DEGREE>& p,
                  const PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& gQ);
    PQPolynomials(const PQPolynomials& polynomials);
    PQPolynomials& operator=(const PQPolynomials& polynomials);
    const Polynomial<SGS::P_POLYNOMIAL_DEGREE>& getP() const;
    Polynomial<SGS::P_POLYNOMIAL_DEGREE>& getP();
    const PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& getQ() const;
    PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& getQ();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & getP();
        archive & getQ();
    }
};

#endif // PQPOLYNOMIALS_HPP
