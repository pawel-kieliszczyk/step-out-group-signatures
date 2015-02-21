/**
 * @file BasicSymmetricCipher.hpp
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
 * This file contains the basic class
 * which implements cipher algorithms.
 */

#ifndef BASICSYMMETRICCIPHER_HPP
#define	BASICSYMMETRICCIPHER_HPP

#include "IBasicSymmetricCipher.hpp"

#include <gcrypt.h>

#include <cstddef>
#include <string>

/**
 * A BasicSymmetricCipher class.
 * This is a template class implementing IBasicSymmetricCipher interface.
 * Id provides implementation for all methods that are necessary
 * to encrypt and decrypt a specified text. Some of the methods
 * use Libgcrypt's functions.
 *
 * @see IBasicSymmetricCipher
 */
template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
class BasicSymmetricCipher : public IBasicSymmetricCipher
{
public:
    /**
     * Default constructor of the BasicSymmetricCipher<Algo, Mode, Flags> class.
     *
     * Creates a BasicSymmetricCipher<Algo, Mode, Flags> object
     * and allocates needed resources.
     */
    BasicSymmetricCipher();

    /**
     * Destructor of the BasicSymmetricCipher<Algo, Mode, Flags> class.
     *
     * Releases the BasicSymmetricCipher<Algo, Mode, Flags> object
     * and frees all associated resources.
     */
    ~BasicSymmetricCipher();
private:
    /**
     * Sets the key used in encryption and decryption algorithm.
     *
     * @param p_key Reference to a string object that stores the key.
     */
    void setKeyImpl(const std::string& p_key);

    /**
     * Sets the key used in encryption and decryption algorithm.
     *
     * @param p_key Pointer to the key.
     * @param p_keyLength Length of the key.
     */
    void setKeyImpl(const void* p_key, const size_t p_keyLength);

    /**
     * Sets the initialization vector used in encryption and decryption algorithm.
     *
     * @param p_iv Reference to a string object that stores the initialization vector.
     */
    void setInitializationVectorImpl(const std::string& p_iv);

    /**
     * Sets the initialization vector used in encryption and decryption algorithm.
     *
     * @param p_iv Pointer to the initialization vector.
     * @param p_ivLength Length of the initialization vector.
     */
    void setInitializationVectorImpl(const void* p_iv, const size_t p_ivLength);

    /**
     * Encrypts a given data. The ciphertext replaces the actual data.
     *
     * @param p_plaintext Pointer to the data.
     * @param p_plaintextLength Length of the data.
     */
    void encryptImpl(void* p_plaintext, const size_t p_plaintextLength);

    /**
     * Decrypts a given data. The decrypted text replaces the actual data.
     *
     * @param p_ciphertext Pointer to the data.
     * @param p_ciphertextLength Length of the data.
     */
    void decryptImpl(void* p_ciphertext, const size_t p_ciphertextLength);

    gcry_cipher_hd_t m_handler; /**< Libgcrypt's handler's type. */
};

template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
BasicSymmetricCipher<Algo, Mode, Flags>::BasicSymmetricCipher()
{
    gcry_cipher_open(&m_handler, Algo, Mode, Flags);
}

template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
BasicSymmetricCipher<Algo, Mode, Flags>::~BasicSymmetricCipher()
{
    gcry_cipher_close(m_handler);
}

template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
void BasicSymmetricCipher<Algo, Mode, Flags>::setKeyImpl(const std::string& p_key)
{
    setKeyImpl(p_key.c_str(), p_key.size());
}

template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
void BasicSymmetricCipher<Algo, Mode, Flags>::setKeyImpl(const void* p_key, const size_t p_keyLength)
{
    gcry_cipher_setkey(m_handler, p_key, p_keyLength);
}

template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
void BasicSymmetricCipher<Algo, Mode, Flags>::setInitializationVectorImpl(const std::string& p_iv)
{
    setInitializationVectorImpl(p_iv.c_str(), p_iv.size());
}

template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
void BasicSymmetricCipher<Algo, Mode, Flags>::setInitializationVectorImpl(const void* p_iv, const size_t p_ivLength)
{
    gcry_cipher_setiv(m_handler, p_iv, p_ivLength);
}

template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
void BasicSymmetricCipher<Algo, Mode, Flags>::encryptImpl(void* p_plaintext, const size_t p_plaintextLength)
{
    gcry_cipher_encrypt(m_handler, p_plaintext, p_plaintextLength, NULL, 0);
}

template<gcry_cipher_algos Algo, gcry_cipher_modes Mode, gcry_cipher_flags Flags>
void BasicSymmetricCipher<Algo, Mode, Flags>::decryptImpl(void* p_ciphertext, const size_t p_ciphertextLength)
{
    gcry_cipher_decrypt(m_handler, p_ciphertext, p_ciphertextLength, NULL, 0);
}

#endif // BASICSYMMETRICCIPHER_HPP
