/**
 * @file StepOutGroupSignaturesConstants.hpp
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

#ifndef STEPOUTGROUPSIGNATURESCONSTANTS_HPP
#define	STEPOUTGROUPSIGNATURESCONSTANTS_HPP

#include <boost/static_assert.hpp>

#include <cstddef>

namespace SGS
{

// Security related constants:
const unsigned int   COEFFICIENTS_NBITS         = 64;                            /**< Number of bits of polynomials' coefficients. */
const unsigned int   RSA_KEY_NBITS              = 2048;                          /**< Number of bits of RSA key. */

// Step-out Group Signature scheme's specific constants:
const std::size_t    ALPHA                      = 12;
const std::size_t    BETA                       = 10;
const std::size_t    ETA                        = 300;
const std::size_t    GAMMA                      = 17;
const std::size_t    N                          = 20;
const std::size_t    ZETA                       = 300;

// Degrees of scheme specific polynomials:
const std::size_t   A_POLYNOMIAL_DEGREE         = ALPHA;                         /**< A degree of a(t) polynomial. */
const std::size_t   L_POLYNOMIAL_DEGREE         = N;                             /**< A degree of L(t, x) polynomial. */
const std::size_t   L_EXP_POLYNOMIAL_DEGREE     = ALPHA + BETA * N;              /**< A degree of L(t, x(t) polynomial. */
const std::size_t   M_POLYNOMIAL_DEGREE         = GAMMA;                         /**< A degree of m(t) polynomial. */
const std::size_t   P_POLYNOMIAL_DEGREE         = GAMMA - 1;                     /**< A degree of P(t) polynomial. */
const std::size_t   Q_POLYNOMIAL_DEGREE         = ALPHA + BETA * N - GAMMA;      /**< A degree of Q(t) polynomial. */
const std::size_t   QM_POLYNOMIAL_DEGREE        = Q_POLYNOMIAL_DEGREE + GAMMA;   /**< A degree of Q(t)*m(t) polynomial. */
const std::size_t   S_POLYNOMIAL_DEGREE         = GAMMA;                         /**< A degree of S(t) polynomial. */
const std::size_t   X_POLYNOMIAL_DEGREE         = BETA;                          /**< A degree of x(t) polynomial. */

const std::size_t   MAXIMAL_NUMBER_OF_SIGNERS   = N;                             /**< Maximal number of people that can sign together a message. */

const std::size_t   NUMBER_OF_A_POLYNOMIALS     = N + 1;                         /**< Number of a(t) polynomials. */

const std::size_t   NUMBER_OF_FAKE_OPE_VALUES   = ETA;                           /**< Cardinality of fake OPE set. */
const std::size_t   NUMBER_OF_REAL_OPE_VALUES   = ZETA + 1;                      /**< Cardinality of real OPE set. */

const std::size_t   OPE_PROCEDURE_INPUT_SIZE    = NUMBER_OF_FAKE_OPE_VALUES + NUMBER_OF_REAL_OPE_VALUES;
const std::size_t   OPE_PROCEDURE_OUTPUT_SIZE   = OPE_PROCEDURE_INPUT_SIZE;


BOOST_STATIC_ASSERT(NUMBER_OF_REAL_OPE_VALUES > L_EXP_POLYNOMIAL_DEGREE);        /**< Minimal number of points that are necessary to interpolate Q(t) polynomial. */
BOOST_STATIC_ASSERT(P_POLYNOMIAL_DEGREE < S_POLYNOMIAL_DEGREE);                  /**< L(t, x) = P(t) + Q(t) * S(t) */

} // namespace SGS

#endif // STEPOUTGROUPSIGNATURESCONSTANTS_HPP
