/**
 * @file SExpression.hpp
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
 * The file contains SExpression class which which stores s-expressions.
 */

#ifndef SEXPRESSION_HPP
#define	SEXPRESSION_HPP

#include <gcrypt.h>

#include <boost/assert.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/string.hpp>

#include <cstring>

class SExpressionFactory;

/**
 * SExpression class.
 * Wrapper for s-expressions.
 */
class SExpression
{
    friend class boost::serialization::access;
    friend class SExpressionFactory;
public:
    /**
     * Copy constructor of the \c SExpression class.
     *
     * @param sExpression S-expression to be copied.
     */
    SExpression(const SExpression& sExpression);

    /**
     * Assigns a given s-expression. The previous value is lost.
     *
     * @param sExpression S-expression to be copied.
     *
     * @return Reference to the object itself.
     */
    SExpression& operator=(const SExpression& sExpression);

    /**
     * Destructor of the SExpression class.
     */
    ~SExpression();
private:
    /**
     * Private constructor of the SExpression class.
     *
     * Needed for serialization. Creates an empty s-expression.
     */
    SExpression();
    /**
     * Private constructor of \c SExpression class.
     *
     * New instances of \c SExpression class can be done
     * only by \c SExpressionFactory.
     *
     * @see SExpressionFactory
     *
     * @param sExpInit S-expression in Libgcrypt's format.
     */
    SExpression(gcry_sexp_t sExpInit);

    /**
     * Copies a given s-expression.
     *
     * @param sExpToCopy S-expression to be copied.
     */
    void copySExp(gcry_sexp_t sExpToCopy);

    /**
     * Returns the internal representation of stored s-expression.
     *
     * @return Stored s-expression.
     */
    gcry_sexp_t get() const;

    /**
     * Returns length of a given s-expression.
     *
     * @param sExp S-expression of unknown length.
     *
     * @return The length of the given s-expression.
     */
    std::size_t getSExpLength(gcry_sexp_t sExp) const;

    /**
     * Frees the memory and resets the stored s-expression.
     */
    void releaseSExp();

    /**
     * Serializes the class into a given archive.
     *
     * @param archive Archive where the class is to be stored.
     * @param version Version of the archive.
     */
    template<typename Archive>
    void save(Archive& archive, const unsigned int version) const
    {
        std::size_t sExpLength = getSExpLength(sExp);
        char* sExpBuffer = new char[sExpLength];
        std::size_t error = gcry_sexp_sprint(sExp, GCRYSEXP_FMT_DEFAULT, sExpBuffer, sExpLength);
        BOOST_ASSERT(error != 0);
        std::string toSerialize(sExpBuffer, sExpLength);
        archive & toSerialize;
        delete[] sExpBuffer;
    }

    /**
     * Deserializes the class from a given archive.
     *
     * @param archive Archive from which the class is to be deserialized.
     * @param version Version of the archive.
     */
    template<typename Archive>
    void load(Archive& archive, const unsigned int version)
    {
        std::string serialized;
        archive & serialized;
        const int AUTODETECT = 1;
        gcry_sexp_new(&sExp, serialized.c_str(), serialized.size(), AUTODETECT);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    gcry_sexp_t sExp; /**< Libgcrypt's representation of s-expressions. */
};

#endif // SEXPRESSION_HPP
