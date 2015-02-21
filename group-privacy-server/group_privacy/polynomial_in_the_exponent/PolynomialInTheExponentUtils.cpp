/**
 * @file PolynomialInTheExponentUtils.cpp
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

#include "PolynomialInTheExponentUtils.hpp"

namespace PolynomialInTheExponentUtils
{

BigInteger interpolatePolynomialInPoint(const std::vector<BigInteger>& args,
                                        const std::vector<BigInteger>& values,
                                        const BigInteger& x,
                                        const BigInteger& p)
{
    BOOST_ASSERT(args.size() == values.size());
    BigInteger exponentModulo = (p - 1) / 2;
    BOOST_ASSERT(exponentModulo.isPrime());
    BigInteger result(1u);
    for(std::vector<BigInteger>::size_type i = 0; i < args.size(); ++i)
    {
        BigInteger exponent(1u);
        for(std::vector<BigInteger>::size_type j = 0; j < args.size(); ++j)
        {
            if(i == j)
                continue;
            BigInteger numerator = (x - args[j]) % exponentModulo;
            BigInteger denominator = (args[i] - args[j]) % exponentModulo;
            BigInteger odwrotnosc = invm(denominator, exponentModulo);
            BigInteger factor = (numerator * odwrotnosc) % exponentModulo;
            exponent = (exponent * factor) % exponentModulo;
        }
        result = (result * powm(values[i], exponent, p)) % p;
    }
    return result;
}

} // namespace PolynomialInTheExponentUtils
