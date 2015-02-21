/**
 * @file BigIntegerComparisonOperators.hpp
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

#ifndef BIGINTEGERCOMPARISONOPERATORS_HPP
#define	BIGINTEGERCOMPARISONOPERATORS_HPP

#include "BigIntegerClass.hpp"

/**
 * Comparison operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return True if and only if BigInteger objects are equal.
 */
bool operator==(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Comparison operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return True if and only if BigInteger objects are not equal.
 */
bool operator!=(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Comparison operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return True if and only if the left BigInteger object is lower than the right one.
 */
bool operator<(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Comparison operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return True if and only if the left BigInteger object is greater than the right one.
 */
bool operator>(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Comparison operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return True if and only if the left BigInteger object is lower or equal to the right one.
 */
bool operator<=(const BigInteger& p_left, const BigInteger& p_right);

/**
 * Comparison operator.
 *
 * @param p_left Reference to left BigInteger object.
 * @param p_right Reference to right BigInteger object.
 * @return True if and only if the left BigInteger object is greater or equal to the right one.
 */
bool operator>=(const BigInteger& p_left, const BigInteger& p_right);

#endif // BIGINTEGERCOMPARISONOPERATORS_HPP
