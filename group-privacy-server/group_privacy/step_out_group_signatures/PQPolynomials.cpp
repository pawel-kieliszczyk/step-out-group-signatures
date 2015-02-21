/**
PQPolynomials * @author Pawel Kieliszczyk <pawel.kieliszczyk@gmail.com>
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

#include "PQPolynomials.hpp"

PQPolynomials::PQPolynomials() : boost::tuple<Polynomial<SGS::P_POLYNOMIAL_DEGREE>,
                                              PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE> >()
{
}

PQPolynomials::PQPolynomials(const Polynomial<SGS::P_POLYNOMIAL_DEGREE>& p,
                             const PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& gQ)
    : boost::tuple<Polynomial<SGS::P_POLYNOMIAL_DEGREE>,
                   PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE> >(p, gQ)
{
}

PQPolynomials::PQPolynomials(const PQPolynomials& polynomials)
    : boost::tuple<Polynomial<SGS::P_POLYNOMIAL_DEGREE>,
                   PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE> >(polynomials)
{
}

PQPolynomials& PQPolynomials::operator=(const PQPolynomials& polynomials)
{
    boost::tuple<Polynomial<SGS::P_POLYNOMIAL_DEGREE>,
                 PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE> >::operator=(polynomials);
    return *this;
}

const Polynomial<SGS::P_POLYNOMIAL_DEGREE>& PQPolynomials::getP() const
{
    return boost::get<0>(*this);
}

Polynomial<SGS::P_POLYNOMIAL_DEGREE>& PQPolynomials::getP()
{
    return boost::get<0>(*this);
}

const PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& PQPolynomials::getQ() const
{
    return boost::get<1>(*this);
}

PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE>& PQPolynomials::getQ()
{
    return boost::get<1>(*this);
}
