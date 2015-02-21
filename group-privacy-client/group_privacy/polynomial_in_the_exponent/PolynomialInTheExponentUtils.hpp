/**
 * @file PolynomialInTheExponentUtils.hpp
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

#ifndef POLYNOMIALINTHEEXPONENTUTILS_HPP
#define	POLYNOMIALINTHEEXPONENTUTILS_HPP

#include "../mpi/BigInteger.hpp"

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/static_assert.hpp>

#include <cstddef>
#include <vector>

namespace PolynomialInTheExponentUtils
{
namespace LagrangeInterpolationInTheExponent
{

template<std::size_t Size>
inline void fillCoefficientsWithOnes(boost::array<BigInteger, Size>& coefficients)
{
    std::fill(coefficients.begin(), coefficients.end(), 1u);
}

template<std::size_t Size>
boost::array<BigInteger, Size> createSmallPolynomial(const boost::array<BigInteger, Size>& args,
                                                     const std::size_t indexToOmit,
                                                     const BigInteger& p)
{
    boost::array<BigInteger, Size> smallPolynomial;
    smallPolynomial[0] = 1u;
    std::size_t counter = 1;
    for(std::size_t i = 0; i < Size; ++i)
    {
        if(i == indexToOmit)
            continue;
        BigInteger denominator = (args[indexToOmit] - args[i]) % p;
        BigInteger a = invm(denominator, p);
        BigInteger b = (a * (-args[i])) % p;
        for(std::size_t j = counter++; j > 0; --j)
            smallPolynomial[j] = (a * smallPolynomial[j] + b * smallPolynomial[j-1]) % p;
        smallPolynomial[0] = (a * smallPolynomial[0]) % p;
    }
    return smallPolynomial;
}

template<std::size_t Size>
void raiseValueToTheSmallPolynomialPower(const BigInteger& value,
                                         boost::array<BigInteger, Size>& smallPolynomial,
                                         const BigInteger& p)
{
    for(std::size_t i = 0; i < Size; ++i)
        smallPolynomial[i] = powm(value, smallPolynomial[i], p);
}

template<std::size_t Size>
void multiplyCoefficientsBySmallPolynomial(boost::array<BigInteger, Size>& coefficients,
                                           const boost::array<BigInteger, Size>& smallPolynomial,
                                           const BigInteger& p)
{
    for(std::size_t i = 0; i < Size; ++i)
        coefficients[i] = (coefficients[i] * smallPolynomial[i]) % p;
}

template<std::size_t Size>
void reverseCoefficients(boost::array<BigInteger, Size>& coefficients)
{
    std::reverse(coefficients.begin(), coefficients.end());
}

} // namespace LagrangeInterpolationInTheExponent

template<std::size_t D, std::size_t D1, std::size_t D2>
void createPolynomialInTheExponent(boost::array<BigInteger, D>& coefficients,
                                   const boost::array<BigInteger, D1>& polynomialInTheExponent,
                                   const boost::array<BigInteger, D2>& polynomial,
                                   const BigInteger& p)
{
    BOOST_STATIC_ASSERT(D1 + D2 - 1 == D);
    LagrangeInterpolationInTheExponent::fillCoefficientsWithOnes(coefficients);
    for(std::size_t i = 0; i < D1; ++i)
    {
        for(std::size_t j = 0; j < D2; ++j)
        {
            coefficients[i+j] = (coefficients[i+j] * powm(polynomialInTheExponent[i], polynomial[j], p)) % p;
        }
    }
}

template<std::size_t Size>
BigInteger evaluatePolynomialMod(const boost::array<BigInteger, Size>& coefficients,
                                 const BigInteger& param,
                                 const BigInteger& modulo)
{
    BigInteger result(1u);
    BigInteger power(1u);
    BigInteger exponentModulo = modulo - BigInteger(1u);
    BOOST_FOREACH(const BigInteger& coef, coefficients)
    {
        BigInteger factor = coef;
        factor.powm(power, modulo);
        result = (result * factor) % modulo;
        power = (power * param) % exponentModulo;
    }
    return result;
}

template<std::size_t Size>
void interpolatePolynomial(boost::array<BigInteger, Size>& coefficients,
                           const boost::array<BigInteger, Size>& args,
                           const boost::array<BigInteger, Size>& values,
                           const BigInteger& p,
                           const BigInteger& q)
{
    using namespace LagrangeInterpolationInTheExponent;
    fillCoefficientsWithOnes(coefficients);
    for(std::size_t i = 0; i < Size; ++i)
    {
        boost::array<BigInteger, Size> smallPolynomial = createSmallPolynomial(args, i, q);
        raiseValueToTheSmallPolynomialPower(values[i], smallPolynomial, p);
        multiplyCoefficientsBySmallPolynomial(coefficients, smallPolynomial, p);
    }
    reverseCoefficients(coefficients);
}

BigInteger interpolatePolynomialInPoint(const std::vector<BigInteger>& args,
                                        const std::vector<BigInteger>& values,
                                        const BigInteger& x,
                                        const BigInteger& p);

} // namespace PolynomialInTheExponentUtils

#endif // POLYNOMIALINTHEEXPONENTUTILS_HPP
