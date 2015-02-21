/**
 * @file IBasicSymmetricCipher.hpp
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
 * This file contains an interface for classes which
 * implement encryption algorithms.
 */

#ifndef IBASICSYMMETRICCIPHER_HPP
#define	IBASICSYMMETRICCIPHER_HPP

#include <cstddef>
#include <string>

/**
 * An IBasicSymmetricCipher class.
 * An interface for cipher classes. Provides methods
 * that are necessary for encryption of data
 * and forces all inheriting classes to provide their
 * implementation.
 */
class IBasicSymmetricCipher
{
public:
    /**
     * Virtual destructor of the IBasicSymmetricCipher class.
     */
    virtual ~IBasicSymmetricCipher() {}

    /**
     * Sets the key used in encryption and decryption algorithm.
     *
     * @param p_key Reference to a string object that stores the key.
     */
    void setKey(const std::string& p_key)
    {
        setKeyImpl(p_key);
    }

    /**
     * Sets the key used in encryption and decryption algorithm.
     *
     * @param p_key Pointer to the key.
     * @param p_keyLength Length of the key.
     */
    void setKey(const void* p_key, const size_t p_keyLength)
    {
        setKeyImpl(p_key, p_keyLength);
    }

    /**
     * Sets the initialization vector used in encryption and decryption algorithm.
     *
     * @param p_iv Reference to a string object that stores the initialization vector.
     */
    void setInitializationVector(const std::string& p_iv)
    {
        setInitializationVectorImpl(p_iv);
    }

    /**
     * Sets the initialization vector used in encryption and decryption algorithm.
     *
     * @param p_iv Pointer to the initialization vector.
     * @param p_ivLength Length of the initialization vector.
     */
    void setInitializationVector(const void* p_iv, const size_t p_ivLength)
    {
        setInitializationVectorImpl(p_iv, p_ivLength);
    }

    /**
     * Encrypts a given data. The ciphertext replaces the actual data.
     *
     * @param p_plaintext Pointer to the data.
     * @param p_plaintextLength Length of the data.
     */
    void encrypt(void* p_plaintext, const size_t p_plaintextLength)
    {
        encryptImpl(p_plaintext, p_plaintextLength);
    }

    /**
     * Decrypts a given data. The decrypted text replaces the actual data.
     *
     * @param p_ciphertext Pointer to the data.
     * @param p_ciphertextLength Length of the data.
     */
    void decrypt(void* p_ciphertext, const size_t p_ciphertextLength)
    {
        decryptImpl(p_ciphertext, p_ciphertextLength);
    }
private:
    /**
     * Pure virtual function for implementation
     * of the setKey(const std::string&) method.
     *
     * @param p_key Reference to a string object that stores the key.
     */
    virtual void setKeyImpl(const std::string& p_key) = 0;

    /**
     * Pure virtual function for implementation
     * of the setKey(const void*, const size_t) method.
     *
     * @param p_key Pointer to the key.
     * @param p_keyLength Length of the key.
     */
    virtual void setKeyImpl(const void* p_key, const size_t p_keyLength) = 0;

    /**
     * Pure virtual function for implementation
     * of the setInitializationVector(const std::string&) method.
     *
     * @param p_iv Reference to a string object that stores the key.
     */
    virtual void setInitializationVectorImpl(const std::string& p_iv) = 0;

    /**
     * Pure virtual function for implementation
     * of the setInitializationVector(const void*, const size_t) method.
     *
     * @param p_iv Pointer to the key.
     * @param p_ivLength Length of the key.
     */
    virtual void setInitializationVectorImpl(const void* p_iv, const size_t p_ivLength) = 0;

    /**
     * Pure virtual function for implementation
     * of the encrypt(void*, const size_t) method.
     *
     * @param p_plaintext Pointer to the data.
     * @param p_palintextLength Length of the data.
     */
    virtual void encryptImpl(void* p_plaintext, const size_t p_plaintextLength) = 0;

    /**
     * Pure virtual function for implementation
     * of the decrypt(void*, const size_t) method.
     *
     * @param p_ciphertext Pointer to the data.
     * @param p_ciphertextLength Length of the data.
     */
    virtual void decryptImpl(void* p_ciphertext, const size_t p_ciphertextLength) = 0;
};

#endif // IBASICSYMMETRICCIPHER_HPP
