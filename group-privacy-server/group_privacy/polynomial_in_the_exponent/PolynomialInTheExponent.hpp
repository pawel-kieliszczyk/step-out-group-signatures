/**
 * @file PolynomialInTheExponent.hpp
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

#ifndef POLYNOMIALINTHEEXPONENT_HPP
#define	POLYNOMIALINTHEEXPONENT_HPP

#include "../mpi/BigInteger.hpp"
#include "../polynomial/Polynomial.hpp"
#include "PolynomialInTheExponentUtils.hpp"

#include <boost/array.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/access.hpp>
#include <boost/static_assert.hpp>

#include <cstddef>

template<std::size_t D>
class PolynomialInTheExponent
{
    friend class boost::serialization::access;
public:
    PolynomialInTheExponent();
    PolynomialInTheExponent(const Polynomial<D>& polynomial,
                            const BigInteger& g,
                            const BigInteger& r,
                            const BigInteger& p);
    template<std::size_t D1, std::size_t D2>
    PolynomialInTheExponent(const PolynomialInTheExponent<D1>& polynomialInTheExponent,
                            const Polynomial<D2>& polynomial,
                            const BigInteger& p);
    PolynomialInTheExponent(const PolynomialInTheExponent& polynomialInTheExponent);
    PolynomialInTheExponent& operator=(const PolynomialInTheExponent& polynomialInTheExponent);
    BigInteger* begin();
    BigInteger* end();
    BigInteger& operator[](const std::size_t i);
    const BigInteger& operator[](const std::size_t i) const;
    BigInteger operator()(const BigInteger& param, const BigInteger& modulo) const;
    const boost::array<BigInteger, D+1>& getCoefficients() const;
    void interpolate(boost::array<BigInteger, D+1>& args,
                     boost::array<BigInteger, D+1>& values,
                     const BigInteger& p,
                     const BigInteger& q);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & coefficients;
    }

    boost::array<BigInteger, D+1> coefficients;
};

template<std::size_t D>
PolynomialInTheExponent<D>::PolynomialInTheExponent() : coefficients()
{
}

template<std::size_t D>
PolynomialInTheExponent<D>::PolynomialInTheExponent(const Polynomial<D>& polynomial,
                                                    const BigInteger& g,
                                                    const BigInteger& r,
                                                    const BigInteger& p)
{
    BigInteger coefInit = g;
    coefInit.powm(r, p);
    for(std::size_t i = 0; i < coefficients.size(); ++i)
    {
        coefficients[i] = coefInit;
        coefficients[i].powm(polynomial[i], p);
    }
}

template<std::size_t D>
template<std::size_t D1, std::size_t D2>
PolynomialInTheExponent<D>::PolynomialInTheExponent(const PolynomialInTheExponent<D1>& polynomialInTheExponent,
                                                    const Polynomial<D2>& polynomial,
                                                    const BigInteger& p)
{
    BOOST_STATIC_ASSERT(D1 + D2 == D);
    PolynomialInTheExponentUtils::createPolynomialInTheExponent(coefficients,
                                                                polynomialInTheExponent.getCoefficients(),
                                                                polynomial.getCoefficients(),
                                                                p);
}

template<std::size_t D>
PolynomialInTheExponent<D>::PolynomialInTheExponent(const PolynomialInTheExponent<D>& polynomialInTheExponent)
    : coefficients(polynomialInTheExponent.coefficients)
{
}

template<std::size_t D>
PolynomialInTheExponent<D>&
PolynomialInTheExponent<D>::operator=(const PolynomialInTheExponent<D>& polynomialInTheExponent)
{
    coefficients = polynomialInTheExponent.coefficients;
    return *this;
}

template<std::size_t D>
BigInteger* PolynomialInTheExponent<D>::begin()
{
    return coefficients.begin();
}

template<std::size_t D>
BigInteger* PolynomialInTheExponent<D>::end()
{
    return coefficients.end();
}

template<std::size_t D>
BigInteger& PolynomialInTheExponent<D>::operator[](const std::size_t i)
{
    return coefficients[i];
}

template<std::size_t D>
const BigInteger& PolynomialInTheExponent<D>::operator[](const std::size_t i) const
{
    return coefficients[i];
}

template<std::size_t D>
BigInteger PolynomialInTheExponent<D>::operator()(const BigInteger& param, const BigInteger& modulo) const
{
    return PolynomialInTheExponentUtils::evaluatePolynomialMod(coefficients, param, modulo);
}

template<std::size_t D>
const boost::array<BigInteger, D+1>& PolynomialInTheExponent<D>::getCoefficients() const
{
    return coefficients;
}

template<std::size_t D>
void PolynomialInTheExponent<D>::interpolate(boost::array<BigInteger, D+1>& args,
                                             boost::array<BigInteger, D+1>& values,
                                             const BigInteger& p,
                                             const BigInteger& q)
{
    PolynomialInTheExponentUtils::interpolatePolynomial(coefficients, args, values, p, q);
}

#endif // POLYNOMIALINTHEEXPONENT_HPP
