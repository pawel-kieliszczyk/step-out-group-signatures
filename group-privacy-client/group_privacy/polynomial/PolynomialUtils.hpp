/**
 * @file PolynomialUtils.hpp
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

#ifndef POLYNOMIALUTILS_HPP
#define	POLYNOMIALUTILS_HPP

#include "../mpi/BigInteger.hpp"

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>

namespace PolynomialUtils
{
namespace LagrangeInterpolation
{

template<std::size_t Size>
inline void fillCoefficientsWithZeros(boost::array<BigInteger, Size>& coefficients)
{
    std::fill(coefficients.begin(), coefficients.end(), 0u);
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
void multiplySmallPolynomialByValue(boost::array<BigInteger, Size>& smallPolynomial,
                                    const BigInteger& value,
                                    const BigInteger& p)
{
    for(std::size_t i = 0; i < Size; ++i)
        smallPolynomial[i] = (smallPolynomial[i] * value) % p;
}

template<std::size_t Size>
void addSmallPolynomialToCoefficients(const boost::array<BigInteger, Size>& smallPolynomial,
                                      boost::array<BigInteger, Size>& coefficients,
                                      const BigInteger& p)
{
    for(std::size_t i = 0; i < Size; ++i)
        coefficients[i] = (coefficients[i] + smallPolynomial[i]) % p;
}

template<std::size_t Size>
void reverseCoefficients(boost::array<BigInteger, Size>& coefficients)
{
    std::reverse(coefficients.begin(), coefficients.end());
}

} // namespace LagrangeInterpolation

template<std::size_t Size>
BigInteger evaluatePolynomialMod(const boost::array<BigInteger, Size>& coefficients,
                                 const BigInteger& param,
                                 const BigInteger& modulo)
{
    // Horner scheme
    BOOST_ASSERT(coefficients.size());
    BigInteger result = 0u;
    BOOST_REVERSE_FOREACH(const BigInteger& coef, coefficients)
        result = (result * param + coef) % modulo;
    return result;
}

template<std::size_t Size>
void interpolatePolynomialMod(const boost::array<BigInteger, Size>& args,
                              const boost::array<BigInteger, Size>& values,
                              boost::array<BigInteger, Size>& coefficients,
                              const BigInteger& p)
{
    // Lagrange interpolation
    using namespace LagrangeInterpolation;
    fillCoefficientsWithZeros(coefficients);
    for(std::size_t i = 0; i < Size; ++i)
    {
        boost::array<BigInteger, Size> smallPolynomial = createSmallPolynomial(args, i, p);
        multiplySmallPolynomialByValue(smallPolynomial, values[i], p);
        addSmallPolynomialToCoefficients(smallPolynomial, coefficients, p);
    }
    reverseCoefficients(coefficients);
}

} // namespace PolynomialUtils

#endif // POLYNOMIALUTILS_HPP
