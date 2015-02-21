/**
 * @file BigIntegerComparisonOperators.cpp
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

#include "BigIntegerComparisonOperators.hpp"

#include "BigIntegerClass.hpp"

#include <gcrypt.h>

bool operator==(const BigInteger& p_left, const BigInteger& p_right)
{
    return (gcry_mpi_cmp(p_left.m_mpi, p_right.m_mpi) == 0);
}

bool operator!=(const BigInteger& p_left, const BigInteger& p_right)
{
    return (gcry_mpi_cmp(p_left.m_mpi, p_right.m_mpi) != 0);
}

bool operator<(const BigInteger& p_left, const BigInteger& p_right)
{
    return (gcry_mpi_cmp(p_left.m_mpi, p_right.m_mpi) < 0);
}

bool operator>(const BigInteger& p_left, const BigInteger& p_right)
{
    return (gcry_mpi_cmp(p_left.m_mpi, p_right.m_mpi) > 0);
}

bool operator<=(const BigInteger& p_left, const BigInteger& p_right)
{
    return (gcry_mpi_cmp(p_left.m_mpi, p_right.m_mpi) <= 0);
}

bool operator>=(const BigInteger& p_left, const BigInteger& p_right)
{
    return (gcry_mpi_cmp(p_left.m_mpi, p_right.m_mpi) >= 0);
}
