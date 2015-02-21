/**
 * @file BigIntegerClass.cpp
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

#include "BigIntegerClass.hpp"

#include "BigIntegerComparisonOperators.hpp"

#include <boost/assert.hpp>

#include <cstddef>

BigInteger::BigInteger()
{
    m_mpi = gcry_mpi_new(0);
}

BigInteger::BigInteger(const BigInteger& p_bigInteger)
{
    m_mpi = gcry_mpi_set(NULL, p_bigInteger.m_mpi);
}

BigInteger::BigInteger(const unsigned long p_value)
{
    m_mpi = gcry_mpi_set_ui(NULL, p_value);
}

BigInteger::BigInteger(const std::string& hexValue)
{
    gcry_error_t error = gcry_mpi_scan(&m_mpi, GCRYMPI_FMT_HEX, hexValue.c_str(), 0, NULL);
    BOOST_ASSERT(!error);
}

BigInteger::~BigInteger()
{
    gcry_mpi_release(m_mpi);
}

BigInteger& BigInteger::operator=(const BigInteger& p_bigInteger)
{
    m_mpi = gcry_mpi_copy(p_bigInteger.m_mpi);
    return *this;
}

BigInteger& BigInteger::operator=(const unsigned long p_value)
{
    gcry_mpi_set_ui(m_mpi, p_value);
    return *this;
}

void BigInteger::set(const BigInteger& p_bigInteger)
{
    m_mpi = gcry_mpi_copy(p_bigInteger.m_mpi);
}

void BigInteger::set(const unsigned long p_value)
{
    gcry_mpi_set_ui(m_mpi, p_value);
}

const BigInteger& BigInteger::operator+() const
{
    return *this;
}

const BigInteger BigInteger::operator-() const
{
    BigInteger l_result(*this);
    l_result -= *this;
    l_result -= *this;
    return l_result;
}

const BigInteger& BigInteger::operator++()
{
    BigInteger l_copy(*this);
    gcry_mpi_add_ui(m_mpi, l_copy.m_mpi, 1u);
    return *this;
}

const BigInteger BigInteger::operator++(int)
{
    BigInteger l_result(*this);
    gcry_mpi_add_ui(m_mpi, l_result.m_mpi, 1u);
    return l_result;
}

const BigInteger& BigInteger::operator--()
{
    BigInteger l_copy(*this);
    gcry_mpi_sub_ui(m_mpi, l_copy.m_mpi, 1u);
    return *this;
}

const BigInteger BigInteger::operator--(int)
{
    BigInteger l_result(*this);
    gcry_mpi_sub_ui(m_mpi, l_result.m_mpi, 1u);
    return l_result;
}

BigInteger& BigInteger::operator+=(const BigInteger& p_bigInteger)
{
    BigInteger l_copy(*this);
    gcry_mpi_add(m_mpi, l_copy.m_mpi, p_bigInteger.m_mpi);
    return *this;
}

BigInteger& BigInteger::operator+=(const unsigned long p_value)
{
    BigInteger l_copy(*this);
    gcry_mpi_add_ui(m_mpi, l_copy.m_mpi, p_value);
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& p_bigInteger)
{
    BigInteger l_copy(*this);
    gcry_mpi_sub(m_mpi, l_copy.m_mpi, p_bigInteger.m_mpi);
    return *this;
}

BigInteger& BigInteger::operator-=(const unsigned long p_value)
{
    BigInteger l_copy(*this);
    gcry_mpi_sub_ui(m_mpi, l_copy.m_mpi, p_value);
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& p_bigInteger)
{
    BigInteger l_copy(*this);
    gcry_mpi_mul(m_mpi, l_copy.m_mpi, p_bigInteger.m_mpi);
    return *this;
}

BigInteger& BigInteger::operator*=(const unsigned long p_value)
{
    BigInteger l_copy(*this);
    gcry_mpi_mul_ui(m_mpi, l_copy.m_mpi, p_value);
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& p_bigInteger)
{
    BigInteger l_copy(*this);
    gcry_mpi_div(m_mpi, NULL, l_copy.m_mpi, p_bigInteger.m_mpi, 0);
    return *this;
}

BigInteger& BigInteger::operator/=(const unsigned long p_value)
{
    BigInteger l_copy(*this);
    BigInteger l_bigInteger(p_value);
    gcry_mpi_div(m_mpi, NULL, l_copy.m_mpi, l_bigInteger.m_mpi, 0);
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& p_bigInteger)
{
    BigInteger l_copy(*this);
    gcry_mpi_mod(m_mpi, l_copy.m_mpi, p_bigInteger.m_mpi);
    return *this;
}

BigInteger& BigInteger::operator%=(const unsigned long p_value)
{
    BigInteger l_copy(*this);
    BigInteger l_bigInteger(p_value);
    gcry_mpi_mod(m_mpi, l_copy.m_mpi, l_bigInteger.m_mpi);
    return *this;
}

BigInteger& BigInteger::powm(const BigInteger& p_power, const BigInteger& p_mod)
{
    BigInteger l_copy(*this);
    gcry_mpi_powm(m_mpi, l_copy.m_mpi, p_power.m_mpi, p_mod.m_mpi);
    return *this;
}

BigInteger& BigInteger::invm(const BigInteger& p_inv, const BigInteger& p_mod)
{
    gcry_mpi_invm(m_mpi, p_inv.m_mpi, p_mod.m_mpi);
    return *this;
}

bool BigInteger::isPrime() const
{
    return (gcry_prime_check(m_mpi, 0) == 0);
}
