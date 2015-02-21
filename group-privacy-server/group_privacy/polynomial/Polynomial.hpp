/**
 * @file Polynomial.hpp
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

#ifndef POLYNOMIAL_HPP
#define	POLYNOMIAL_HPP

#include "../mpi/BigInteger.hpp"
#include "PolynomialUtils.hpp"

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/access.hpp>

#include <cstddef>
#include <iterator>

template<std::size_t D>
class Polynomial
{
    friend class boost::serialization::access;
public:
    Polynomial();
    Polynomial(const boost::array<BigInteger, D+1>& coefficientsInit);
    Polynomial(const Polynomial& polynomial);
    Polynomial& operator=(const Polynomial& polynomial);
    BigInteger* begin();
    BigInteger* end();
    BigInteger& operator[](const std::size_t i);
    const BigInteger& operator[](const std::size_t i) const;
    BigInteger operator()(const BigInteger& param, const BigInteger& modulo) const;
    const boost::array<BigInteger, D+1>& getCoefficients() const;
    void interpolate(const boost::array<BigInteger, D+1>& args,
                     const boost::array<BigInteger, D+1>& values,
                     const BigInteger& p);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & coefficients;
    }

    boost::array<BigInteger, D+1> coefficients;
};

template<std::size_t D>
Polynomial<D>::Polynomial() : coefficients()
{
}

template<std::size_t D>
Polynomial<D>::Polynomial(const boost::array<BigInteger, D+1>& coefficientsInit)
{
    coefficients = coefficientsInit;
}

template<std::size_t D>
Polynomial<D>::Polynomial(const Polynomial<D>& polynomial) : coefficients(polynomial.coefficients)
{
}

template<std::size_t D>
Polynomial<D>& Polynomial<D>::operator=(const Polynomial<D>& polynomial)
{
    coefficients = polynomial.coefficients;
    return *this;
}

template<std::size_t D>
BigInteger* Polynomial<D>::begin()
{
    return coefficients.begin();
}

template<std::size_t D>
BigInteger* Polynomial<D>::end()
{
    return coefficients.end();
}

template<std::size_t D>
BigInteger& Polynomial<D>::operator[](const std::size_t i)
{
    return coefficients[i];
}

template<std::size_t D>
const BigInteger& Polynomial<D>::operator[](const std::size_t i) const
{
    return coefficients[i];
}

template<std::size_t D>
BigInteger Polynomial<D>::operator()(const BigInteger& param, const BigInteger& modulo) const
{
    return PolynomialUtils::evaluatePolynomialMod(coefficients, param, modulo);
}

template<std::size_t D>
const boost::array<BigInteger, D+1>& Polynomial<D>::getCoefficients() const
{
    return coefficients;
}

template<std::size_t D>
void Polynomial<D>::interpolate(const boost::array<BigInteger, D+1>& args,
                                const boost::array<BigInteger, D+1>& values,
                                const BigInteger& p)
{
    PolynomialUtils::interpolatePolynomialMod(args, values, coefficients, p);
    BOOST_FOREACH(const BigInteger& coefficient, coefficients)
        BOOST_ASSERT(coefficient < p);
}

template<std::size_t LeftSize, std::size_t RightSize, std::size_t OutputSize>
Polynomial<OutputSize> add(const Polynomial<LeftSize>& left,
                           const Polynomial<RightSize>& right,
                           const BigInteger& modulo)
{
    return Polynomial<OutputSize>(
        PolynomialUtils::addPolynomials<LeftSize+1, RightSize+1, OutputSize+1>(left.getCoefficients(),
                                                                               right.getCoefficients(),
                                                                               modulo));
}

template<std::size_t LeftSize, std::size_t RightSize, std::size_t OutputSize>
Polynomial<OutputSize> multiply(const Polynomial<LeftSize>& left,
                                const Polynomial<RightSize>& right,
                                const BigInteger& modulo)
{
    return Polynomial<OutputSize>(
        PolynomialUtils::multiplyPolynomials<LeftSize+1, RightSize+1, OutputSize+1>(left.getCoefficients(),
                                                                                   right.getCoefficients(),
                                                                                   modulo));
}

template<std::size_t LeftSize, std::size_t RightSize, std::size_t OutputSize>
Polynomial<OutputSize> divide(const Polynomial<LeftSize>& left,
                              const Polynomial<RightSize>& right,
                              const BigInteger& modulo)
{
    return Polynomial<OutputSize>(
        PolynomialUtils::dividePolynomials<LeftSize+1, RightSize+1, OutputSize+1>(left.getCoefficients(),
                                                                                  right.getCoefficients(),
                                                                                  modulo));
}

template<std::size_t LeftSize, std::size_t RightSize, std::size_t OutputSize>
Polynomial<OutputSize> mod(const Polynomial<LeftSize>& left,
                           const Polynomial<RightSize>& right,
                           const BigInteger& modulo)
{
    return Polynomial<OutputSize>(
        PolynomialUtils::moduloPolynomials<LeftSize+1, RightSize+1, OutputSize+1>(left.getCoefficients(),
                                                                                  right.getCoefficients(),
                                                                                  modulo));
}

template<std::size_t InputSize, std::size_t OutputSize>
Polynomial<OutputSize> pow(const Polynomial<InputSize>& polynomial, const std::size_t n, const BigInteger& modulo)
{
    return Polynomial<OutputSize>(PolynomialUtils::powm<InputSize+1, OutputSize+1>(polynomial.getCoefficients(),
                                                                                   n,
                                                                                   modulo));
}

#endif // POLYNOMIAL_HPP
