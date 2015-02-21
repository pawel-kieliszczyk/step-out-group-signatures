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
void reverseCoefficients(boost::array<BigInteger, Size>& coefficients)
{
    std::reverse(coefficients.begin(), coefficients.end());
}

} // namespace LagrangeInterpolation

template<std::size_t Size>
inline void fillCoefficientsWithZeros(boost::array<BigInteger, Size>& coefficients)
{
    std::fill(coefficients.begin(), coefficients.end(), 0u);
}

template<std::size_t Size>
void shiftToRight(boost::array<BigInteger, Size>& array, const std::size_t k)
{
    //std::cout << "lol 1: " << Size << " " << k << std::endl;
    for(std::size_t j = Size - 1; j > k; --j)
        array[j] = array[j-k];
    array[k] = array[0];
    for(std::size_t j = 0; j < k; ++j)
        array[j] = 0u;
    //std::cout << "lol 2" << std::endl;
}

template<std::size_t Size>
void addSmallPolynomialToCoefficients(const boost::array<BigInteger, Size>& smallPolynomial,
                                      boost::array<BigInteger, Size>& coefficients,
                                      const BigInteger& p)
{
    for(std::size_t i = 0; i < Size; ++i)
        coefficients[i] = (coefficients[i] + smallPolynomial[i]) % p;
}

template<std::size_t InputSize, std::size_t OutputSize>
void multiplyCoefficientsByPolynomial(boost::array<BigInteger, OutputSize>& coefficients,
                                      const boost::array<BigInteger, InputSize>& polynomial,
                                      const BigInteger& modulo)
{
    boost::array<BigInteger, OutputSize> coefficientsCopy;
    std::copy(coefficients.begin(), coefficients.end(), coefficientsCopy.begin());
    fillCoefficientsWithZeros(coefficients);
    for(std::size_t i = 0; i < InputSize; ++i)
    {
        boost::array<BigInteger, OutputSize> element;
        std::copy(coefficientsCopy.begin(), coefficientsCopy.end(), element.begin());
        for(std::size_t j = 0; j < OutputSize; ++j)
        {
            element[j] = (element[j] * polynomial[i]) % modulo;
        }
        shiftToRight(element, i);
        addSmallPolynomialToCoefficients(element, coefficients, modulo);
    }
}

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

template<std::size_t LeftSize, std::size_t RightSize, std::size_t OutputSize>
boost::array<BigInteger, OutputSize> addPolynomials(const boost::array<BigInteger, LeftSize>& left,
                                                    const boost::array<BigInteger, RightSize>& right,
                                                    const BigInteger& modulo)
{
    BOOST_ASSERT(LeftSize >= RightSize && OutputSize >= LeftSize);
    boost::array<BigInteger, OutputSize> coefficients;
    std::copy(left.begin(), left.end(), coefficients.begin());
    for(std::size_t i = 0; i < RightSize; ++i)
        coefficients[i] = (coefficients[i] + right[i]) % modulo;
    return coefficients;
}

template<std::size_t LeftSize, std::size_t RightSize, std::size_t OutputSize>
boost::array<BigInteger, OutputSize> multiplyPolynomials(const boost::array<BigInteger, LeftSize>& left,
                                                         const boost::array<BigInteger, RightSize>& right,
                                                         const BigInteger& modulo)
{
    BOOST_ASSERT(OutputSize - 1 == (LeftSize - 1) + (RightSize - 1));
    boost::array<BigInteger, OutputSize> coefficients;
    std::copy(left.begin(), left.end(), coefficients.begin());
    multiplyCoefficientsByPolynomial(coefficients, right, modulo);
    return coefficients;
}

template<std::size_t LeftSize, std::size_t RightSize, std::size_t OutputSize>
boost::array<BigInteger, OutputSize> dividePolynomials(boost::array<BigInteger, LeftSize> left,
                                                       const boost::array<BigInteger, RightSize>& right,
                                                       const BigInteger& modulo)
{
    BOOST_ASSERT(OutputSize - 1 == LeftSize - RightSize);
    boost::array<BigInteger, OutputSize> coefficients;
    fillCoefficientsWithZeros(coefficients);
    std::size_t k = OutputSize - 1;
    while(true)
    {
        coefficients[k] = (left[RightSize + k - 1] * invm(right.back(), modulo)) % modulo;
        for(std::size_t j = RightSize + k - 1; j > k; --j)
            left[j] = (left[j] - coefficients[k] * right[j-k]) % modulo;
        left[k] = (left[k] - coefficients[k] * right.front()) % modulo;
        if(k-- == 0)
            break;
    }
    return coefficients;
}

template<std::size_t LeftSize, std::size_t RightSize, std::size_t OutputSize>
boost::array<BigInteger, OutputSize> moduloPolynomials(boost::array<BigInteger, LeftSize> left,
                                                       const boost::array<BigInteger, RightSize>& right,
                                                       const BigInteger& modulo)
{
    BOOST_ASSERT(OutputSize == RightSize - 1);
    std::size_t k = LeftSize - RightSize;
    while(true)
    {
        BigInteger q = (left[RightSize + k - 1] * invm(right.back(), modulo)) % modulo;
        for(std::size_t j = RightSize + k - 1; j > k; --j)
            left[j] = (left[j] - q * right[j-k]) % modulo;
        left[k] = (left[k] - q * right.front()) % modulo;
        if(k-- == 0)
            break;
    }
    boost::array<BigInteger, OutputSize> coefficients;
    for(std::size_t i = 0; i < coefficients.size(); ++i)
        coefficients[i] = left[i];
    return coefficients;
}

template<std::size_t InputSize, std::size_t OutputSize>
boost::array<BigInteger, OutputSize> powm(const boost::array<BigInteger, InputSize>& polynomial,
                                          const std::size_t n,
                                          const BigInteger& modulo)
{
    BOOST_ASSERT(OutputSize - 1 >= (InputSize - 1) * n);
    boost::array<BigInteger, OutputSize> coefficients;
    fillCoefficientsWithZeros(coefficients);
    coefficients.front() = 1u;
    for(std::size_t i = 0; i < n; ++i)
        multiplyCoefficientsByPolynomial(coefficients, polynomial, modulo);
    return coefficients;
}

} // namespace PolynomialUtils

#endif // POLYNOMIALUTILS_HPP
