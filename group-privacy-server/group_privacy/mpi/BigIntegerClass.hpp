/**
 * @file BigIntegerClass.hpp
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
 *
 * This file contains the BigInteger class
 * which implements multiple precision integer type.
 * There are also declarations of all necessary
 * arithmetic operators that manipulate objects
 * of this class.
 */

#ifndef BIGINTEGERCLASS_HPP
#define	BIGINTEGERCLASS_HPP

#include <boost/serialization/string.hpp>
#include <boost/serialization/split_member.hpp>

#include <gcrypt.h>

#include <iosfwd>
#include <string>

/**
 * A BigInteger class.
 * Implements multiple precision integer type using Libgcrypt.
 * Provides all necessary methods needed for a manipulation
 * of numeric values such as arithemetic and comparison operators.
 */
class BigInteger
{
    friend class boost::serialization::access;
    // Friendly comparison operators:
    friend bool operator==(const BigInteger& p_left, const BigInteger& p_right);
    friend bool operator!=(const BigInteger& p_left, const BigInteger& p_right);
    friend bool operator<(const BigInteger& p_left, const BigInteger& p_right);
    friend bool operator>(const BigInteger& p_left, const BigInteger& p_right);
    friend bool operator<=(const BigInteger& p_left, const BigInteger& p_right);
    friend bool operator>=(const BigInteger& p_left, const BigInteger& p_right);
    // Friendly output streamer:
    template<typename charT, typename traits>
    friend std::basic_ostream<charT, traits>&
        operator<<(std::basic_ostream<charT, traits>& p_os, const BigInteger& p_bigInteger);
public:
    /**
     * Prime numbers of \c BigInteger type generator.
     * Implemented as a functor.
     */
    class PrimeGenerator
    {
    public:
        /**
         * Constructor of \c BigInteger::PrimeGenerator class.
         *
         * @param p_nbits Number of bits of numbers to generate.
         */
        PrimeGenerator(const unsigned int p_nbits) : m_nbits(p_nbits) {}

        /**
         * Generates a prime number of \c BigInteger type.
         * @return
         */
        BigInteger operator()()
        {
            BigInteger l_bigInteger;
            gcry_prime_generate(&l_bigInteger.m_mpi, m_nbits, 0, NULL, NULL, NULL, GCRY_STRONG_RANDOM, 0);
            return l_bigInteger;
        }
    private:
        unsigned int m_nbits; /**< Number of bits of numbers to generate. */
    };

    /**
     * Random numbers of \c BigInteger type generator.
     * Implemented as a functor.
     */
    class RandomGenerator
    {
    public:
        /**
         * Constructor of \c BigInteger::RandomGenerator class.
         *
         * @param p_nbits Number of bits of numbers to generate.
         */
        RandomGenerator(const unsigned int p_nbits) : m_nbits(p_nbits) {}

        /**
         * Generates a random number of \c BigInteger type.
         * @return
         */
        BigInteger operator()()
        {
            BigInteger l_bigInteger;
            gcry_mpi_randomize(l_bigInteger.m_mpi, m_nbits, GCRY_STRONG_RANDOM);
            return l_bigInteger;
        }
    private:
        unsigned int m_nbits; /**< Number of bits of numbers to generate. */
    };

    /**
     * Default constructor of the BigInteger class.
     *
     * Allocates a new BigInteger object
     * and initializes it to 0.
     */
    BigInteger();

    /**
     * Copy constructor of the BigInteger class.
     *
     * Creates a new BigInteger object
     * as the exact copy of a given parameter.
     *
     * @param p_bigInteger Reference to a BigInteger object which will be copied.
     */
    BigInteger(const BigInteger& p_bigInteger);

    /**
     * Constructor of the BigInteger class.
     *
     * Creates a new BigInteger object
     * and initializes it to a given parameter.
     *
     * @param p_value Value to initialize a BigInteger object.
     */
    BigInteger(const unsigned long p_value);

    /**
     * Constructor of the BigInteger class.
     *
     * Creates a new BigInteger object
     * and initializes it to a given parameter.
     *
     * @param haxValue String containing hex representation of multi precision number.
     */
    BigInteger(const std::string& hexValue);

    /**
     * Destructor of the BigInteger class.
     *
     * Releases the BigInteger object
     * and frees all associated resources.
     */
    ~BigInteger();

    /**
     * Assignment operator.
     *
     * Assigns value of a given parameter
     * to the BigInteger object and returns itself.
     *
     * @param p_bigInteger Reference to a BigInteger object to be copied.
     * @return Reference to the BigInteger object.
     */
    BigInteger& operator=(const BigInteger& p_bigInteger);

    /**
     * Assignment operator.
     *
     * Assigns value of a given parameter
     * to the BigInteger object.
     *
     * @param p_value Value which the BigInteger object will be set to.
     * @return Reference to the BigInteger object.
     */
    BigInteger& operator=(const unsigned long p_value);

    /**
     * Assigns value of a given parameter
     * to the BigInteger object.
     *
     * @param p_bigInteger Reference to a BigInteger object to be copied.
     */
    void set(const BigInteger& p_bigInteger);

    /**
     * Assigns value of a given parameter
     * to the BigInteger object.
     *
     * @param p_value Value which the BigInteger object will be set to.
     */
    void set(const unsigned long p_value);

    /**
     * Arithemetic operator "plus".
     *
     * Does nothing actually.
     *
     * @return Reference to the BigInteger object.
     */
    const BigInteger& operator+() const;

    /**
     * Arithemetic operator "minus".
     *
     * @return BigInteger object opposite to the current one.
     */
    const BigInteger operator-() const;

    /**
     * Pre increment operator
     *
     * @return Reference to the BigInteger object equal to the value after incrementation.
     */
    const BigInteger& operator++();

    /**
     * Post increment operator.
     *
     * @return BigInteger object equal to the value before incrementation.
     */
    const BigInteger operator++(int);

    /**
     * Pre decrement operator
     *
     * @return Reference to the BigInteger object equal to the value after decrementation.
     */
    const BigInteger& operator--();

    /**
     * Post decrement operator.
     *
     * @return BigInteger object equal to the value before decrementation.
     */
    const BigInteger operator--(int);

    /**
     * Arithmetic operator.
     *
     * Increases the BigInteger object by the given parameter.
     *
     * @param p_bigInteger Reference to a BigInteger object.
     * @return Reference to the BigInteger object after addition;
     */
    BigInteger& operator+=(const BigInteger& p_bigInteger);

    /**
     * Arithmetic operator.
     *
     * Increases the BigInteger object by the given parameter.
     *
     * @param p_value Value which the BigInteger object should be increased by.
     * @return Reference to the BigInteger object after addition;
     */
    BigInteger& operator+=(const unsigned long p_value);

    /**
     * Arithmetic operator.
     *
     * Decreases the BigInteger object by the given parameter.
     *
     * @param p_bigInteger Reference to a BigInteger object.
     * @return Reference to the BigInteger object after subtraction;
     */
    BigInteger& operator-=(const BigInteger& p_bigInteger);

    /**
     * Arithmetic operator.
     *
     * Decreases the BigInteger object by the given parameter.
     *
     * @param p_value Value which the BigInteger object should be decreased by.
     * @return Reference to the BigInteger object after subtraction;
     */
    BigInteger& operator-=(const unsigned long p_value);

    /**
     * Arithmetic operator.
     *
     * Multiplies the BigInteger object by the given parameter.
     *
     * @param p_bigInteger Reference to a BigInteger object.
     * @return Reference to the BigInteger object after multiplication;
     */
    BigInteger& operator*=(const BigInteger& p_bigInteger);

    /**
     * Arithmetic operator.
     *
     * Multiplies the BigInteger object by the given parameter.
     *
     * @param p_value Value which the BigInteger object should be multiplied by.
     * @return Reference to the BigInteger object after multiplication;
     */
    BigInteger& operator*=(const unsigned long p_value);

    /**
     * Arithmetic operator.
     *
     * Divides the BigInteger object by the given parameter.
     *
     * @param p_bigInteger Reference to a BigInteger object.
     * @return Reference to the BigInteger object after division;
     */
    BigInteger& operator/=(const BigInteger& p_bigInteger);

    /**
     * Arithmetic operator.
     *
     * Divides the BigInteger object by the given parameter.
     *
     * @param p_value Value which the BigInteger object should be divided by.
     * @return Reference to the BigInteger object after division;
     */
    BigInteger& operator/=(const unsigned long p_value);

    /**
     * Arithmetic operator.
     *
     * Calculates the rest of division of the BigInteger
     * object by the given parameter and assigns it.
     *
     * @param p_bigInteger Reference to a BigInteger object.
     * @return Reference to the BigInteger object after modulo;
     */
    BigInteger& operator%=(const BigInteger& p_bigInteger);

    /**
     * Arithmetic operator.
     *
     * Calculates the rest of division of the BigInteger
     * object by the given parameter and assigns it.
     *
     * @param p_value Value which the BigInteger object should be divided by.
     * @return Reference to the BigInteger object after modulo;
     */
    BigInteger& operator%=(const unsigned long p_value);

    /**
     * Calculates and assigns the power of the BigInteger object.
     * *this = (*this)^p_power mod p_mod
     *
     * @param p_power Power of the calculation.
     * @param p_mod Modulo value.
     * @return Reference to the BigInteger object after calculation.
     */
    BigInteger& powm(const BigInteger& p_power, const BigInteger& p_mod);

    /**
     * Sets the BigInteger object to the multiplicative inverse
     * of \c p_inv modulo \c p_mod.
     *
     * @param p_inv Reference to the BigInteger object.
     * @param p_mod Modulo value.
     * @return Reference to the BigInteger object after calculation.
     */
    BigInteger& invm(const BigInteger& p_inv, const BigInteger& p_mod);

    /**
     * Checks whether the BigInteger object is a prime number.
     *
     * @return True if BigInteger object is a prime number. False otherwise.
     */
    bool isPrime() const;

    /**
     * Returns \c std::string object containing hex representation
     * of the multi precision number stored in BigInteger object.
     *
     * @return Hexadecimal representation of the multi precision integer.
     */
    std::string toString() const
    {
        unsigned char* l_buffer;
        gcry_mpi_aprint(GCRYMPI_FMT_HEX, &l_buffer, NULL, m_mpi);
        return std::string((const char*)l_buffer);
    }
private:
    template<typename Archive>
    void save(Archive& ar, const unsigned int version) const
    {
        std::string toSerialize = toString();
        ar & toSerialize;
    }
    template<typename Archive>
    void load(Archive& ar, const unsigned int version)
    {
        std::string serialized;
        ar & serialized;
        gcry_mpi_scan(&m_mpi, GCRYMPI_FMT_HEX, serialized.c_str(), 0, NULL);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()

    gcry_mpi_t m_mpi; /**< Libgcrypt's type to wrap multiple precision integer. */
};

/**
 * Enables output streaming.
 *
 * @param p_os Reference to an output stream.
 * @param p_bigInteger Reference to a BigInteger object.
 *
 * @return Reference to an output stream.
 */
template<typename charT, typename traits>
inline std::basic_ostream<charT, traits>&
    operator<<(std::basic_ostream<charT, traits>& p_os, const BigInteger& p_bigInteger)
{
    unsigned char* l_buffer;
    gcry_mpi_aprint(GCRYMPI_FMT_HEX, &l_buffer, NULL, p_bigInteger.m_mpi);
    p_os << (const char*)l_buffer;
    gcry_free(l_buffer);
    return p_os;
}

#endif // BIGINTEGERCLASS_HPP
