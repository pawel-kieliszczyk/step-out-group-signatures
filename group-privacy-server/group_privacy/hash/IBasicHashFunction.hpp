/**
 * @file IBasicHashFunction.hpp
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
 * implement hash functions.
 */

#ifndef IBASICHASHFUNCTION_HPP
#define	IBASICHASHFUNCTION_HPP

#include <cstddef>
#include <string>

/**
 * An IBasicHashFunction class.
 * An interface for hashing classes. Provides methods
 * that are necessary for calculating hash functions
 * and forces all inheriting classes to provide their
 * implementation.
 */
class IBasicHashFunction
{
public:
    /**
     * Virtual destructor of the IBasicHashFunction class.
     */
    virtual ~IBasicHashFunction() {}

    /**
     * Sets the key used in hashing algorithm.
     *
     * @param p_key Reference to a string object that stores the key.
     */
    void setKey(const std::string& p_key)
    {
        setKeyImpl(p_key);
    }

    /**
     * Sets the key used in hashing algorithm.
     *
     * @param p_key Pointer to the key.
     * @param p_keyLength Length of the key.
     */
    void setKey(const void* p_key, const size_t p_keyLength)
    {
        setKeyImpl(p_key, p_keyLength);
    }

    /**
     * Sets the text which should be hashed.
     *
     * @param p_text Reference to a string object that stores the text.
     */
    void setText(const std::string& p_text)
    {
        setTextImpl(p_text);
    }

    /**
     * Sets the text which should be hashed.
     *
     * @param p_text Pointer to the text.
     * @param p_textLength Length of the text.
     */
    void setText(const void* p_text, const size_t p_textLength)
    {
        setTextImpl(p_text, p_textLength);
    }

    /**
     * Calculates a hash value.
     * The text to be hashed has to be set before.
     * The MAC key has to be set before for use
     * with the HMAC feature.
     */
    void calculateHash()
    {
        calculateHashImpl();
    }

    /**
     * Returns the lenth of the hash.
     *
     * @return The length of the hash.
     */
    unsigned int getHashLength()
    {
        return getHashLengthImpl();
    }

    /**
     * Returns hash for the set text.
     *
     * @return Pointer to the hash.
     */
    unsigned char* getHash()
    {
        return getHashImpl();
    }

    /**
     * Returns a string object that contains
     * calculated hash in hexidecimal representation.
     *
     * @return The hash in hexidecimal representation.
     */
    std::string getHexHash()
    {
        return getHexHashImpl();
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
     * of the setText(const std::string&) method.
     *
     * @param p_text Reference to a string object that stores the text.
     */
    virtual void setTextImpl(const std::string& p_text) = 0;

    /**
     * Pure virtual function for implementation
     * of the setText(const void*, const size_t) method.
     *
     * @param p_text Pointer to the text.
     * @param p_textLength Length of the text.
     */
    virtual void setTextImpl(const void* p_text, const size_t p_textLength) = 0;

    /**
     * Pure virtual function for implementation
     * of the calculateHash() method.
     */
    virtual void calculateHashImpl() = 0;

    /**
     * Pure virtual function for implementation
     * of the getHashLength() method.
     *
     * @return The length of the hash.
     */
    virtual unsigned int getHashLengthImpl() = 0;

    /**
     * Pure virtual function for implementation
     * of the getHash() method.
     *
     * @return Pointer to the hash.
     */
    virtual unsigned char* getHashImpl() = 0;

    /**
     * Pure virtual function for implementation
     * of the getHexHash() method.
     *
     * @return The hash in hexidecimal representation.
     */
    virtual std::string getHexHashImpl() = 0;
};

#endif // IBASICHASHFUNCTION_HPP
