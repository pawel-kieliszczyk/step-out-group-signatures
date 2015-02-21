/**
 * @file BigIntegerArithmeticOperators.hpp
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

#ifndef BIGINTEGERARITHMETICOPERATORS_HPP
#define	BIGINTEGERARITHMETICOPERATORS_HPP

#include "BigIntegerClass.hpp"

/**
 * Arithmetic operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return Sum of the given parameters.
 */
const BigInteger operator+(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Arithmetic operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return Difference between the given parameters (p_left - p_right).
 */
const BigInteger operator-(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Arithmetic operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return Product of the given parameters.
 */
const BigInteger operator*(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Arithmetic operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return Quotient of the given parameters (p_left / p_right).
 */
const BigInteger operator/(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Arithmetic operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return Modulo of the given parameters (p_left mod p_right).
 */
const BigInteger operator%(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Calculates \c p_bigInteger ^ \c p_power mod \c p_modulo.
 *
 * @param p_bigInteger Reference to a BigInteger object which is the base of the power.
 * @param p_power Reference to the power of the calculation.
 * @param p_modulo Reference to modulo value of the calculation.
 * @return BigInteger object which equals \c p_bigInteger ^ \c p_power mod \c p_modulo.
 */
const BigInteger powm(const BigInteger& p_bigInteger, const BigInteger& p_power, const BigInteger& p_modulo);

const BigInteger invm(const BigInteger& a, const BigInteger& modulo);

#endif // BIGINTEGERARITHMETICOPERATORS_HPP
