/**
 * @file BasicHashFunction.hpp
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
 * This file contains a basic class
 * which implements calculation of hashes.
 */

#ifndef BASICHASHFUNCTION_HPP
#define	BASICHASHFUNCTION_HPP

#include "IBasicHashFunction.hpp"

#include <gcrypt.h>

#include <cstddef>
#include <iomanip>
#include <sstream>
#include <string>

/**
 * A BasicHashFunction class.
 * This is a template class implementing IBasicHashFunction interface.
 * Id provides implementation for all methods that are necessary
 * to calculate a hash for a specified text. Some of the methods
 * use Libgcrypt's functions.
 *
 * @see IBasicHashFunction
 */
template<gcry_md_algos Algo, gcry_md_flags Flags>
class BasicHashFunction : public IBasicHashFunction
{
public:
    /**
     * Default constructor of the BasicHashFunction<Algo, Flags> class.
     *
     * Creates a BasicHashFunction<Algo, Flags> object
     * and allocates needed resources.
     */
    BasicHashFunction();

    /**
     * Destructor of the BasicHashFunction<Algo, Flags> class.
     *
     * Releases the BasicHashFunction<Algo, Flags> object
     * and frees all associated resources.
     */
    ~BasicHashFunction();
private:
    /**
     * Sets the key used in hashing algorithm.
     *
     * @param p_key Reference to a string object that stores the key.
     */
    void setKeyImpl(const std::string& p_key);

    /**
     * Sets the key used in hashing algorithm.
     *
     * @param p_key Pointer to the key.
     * @param p_keyLength Length of the key.
     */
    void setKeyImpl(const void* p_key, const size_t p_keyLength);

    /**
     * Sets the text which should be hashed.
     *
     * @param p_text Reference to a string object that stores the text.
     */
    void setTextImpl(const std::string& p_text);

    /**
     * Sets the text which should be hashed.
     *
     * @param p_text Pointer to the text.
     * @param p_textLength Length of the text.
     */
    void setTextImpl(const void* p_text, const size_t p_textLength);

    /**
     * Calculates a hash value.
     * The text to be hashed has to be set before.
     * The MAC key has to be set before for use
     * with the HMAC feature.
     */
    void calculateHashImpl();

    /**
     * Returns the lenth of the hash.
     *
     * @return The length of the hash.
     */
    unsigned int getHashLengthImpl();

    /**
     * Returns hash for the set text.
     *
     * @return Pointer to the hash.
     */
    unsigned char* getHashImpl();

    /**
     * Returns a string object that contains
     * calculated hash in hexidecimal representation.
     *
     * @return The hash in hexidecimal representation.
     */
    std::string getHexHashImpl();

    gcry_md_hd_t m_handler; /**< Libgcrypt's handler's type. */
};

template<gcry_md_algos Algo, gcry_md_flags Flags>
BasicHashFunction<Algo, Flags>::BasicHashFunction()
{
    gcry_md_open(&m_handler, Algo, Flags);
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
BasicHashFunction<Algo, Flags>::~BasicHashFunction()
{
    gcry_md_close(m_handler);
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
void BasicHashFunction<Algo, Flags>::setKeyImpl(const std::string& p_key)
{
    setKey(p_key.c_str(), p_key.size());
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
void BasicHashFunction<Algo, Flags>::setKeyImpl(const void* p_key, const size_t p_keyLength)
{
    gcry_md_setkey(m_handler, p_key, p_keyLength);
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
void BasicHashFunction<Algo, Flags>::setTextImpl(const std::string& p_text)
{
    setText(p_text.c_str(), p_text.size());
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
void BasicHashFunction<Algo, Flags>::setTextImpl(const void* p_text, const size_t p_textLength)
{
    gcry_md_write(m_handler, p_text, p_textLength);
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
void BasicHashFunction<Algo, Flags>::calculateHashImpl()
{
    gcry_md_final(m_handler);
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
unsigned int BasicHashFunction<Algo, Flags>::getHashLengthImpl()
{
    return gcry_md_get_algo_dlen(Algo);
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
unsigned char* BasicHashFunction<Algo, Flags>::getHashImpl()
{
    return gcry_md_read(m_handler, Algo);
}

template<gcry_md_algos Algo, gcry_md_flags Flags>
std::string BasicHashFunction<Algo, Flags>::getHexHashImpl()
{
    std::ostringstream l_oss;
    unsigned int l_hashLength = getHashLengthImpl();
    unsigned char* l_hash = getHash();
    for(unsigned int i = 0; i < l_hashLength; ++i)
    {
        l_oss << std::hex << static_cast<int>(l_hash[i]);
    }
    return l_oss.str();
}

#endif // BASICHASHFUNCTION_HPP
