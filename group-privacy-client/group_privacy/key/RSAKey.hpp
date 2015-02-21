/**
 * @file RSAKey.hpp
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
 * This file contains RSAKey class which is responsible
 * for storing an RSA kay
 */

#ifndef RSAKEY_HPP
#define	RSAKEY_HPP

#include "IKey.hpp"

#include <boost/serialization/access.hpp>
#include <boost/shared_ptr.hpp>

/**
 * DigitalSignature class.
 *
 * It stores an RSA key.
 */
class RSAKey : public IKey
{
    friend class boost::serialization::access;
public:
    /**
     * Default constructor of the RSAKey class.
     *
     * It creates aninstance of a class with empty RSA key.
     */
    RSAKey();

    /**
     * Constructor of the RSAKey class.
     *
     * Creates an RSA key based on a given s-expression.
     *
     * @param sExpressionInit S-expression containing an RSA key.
     */
    RSAKey(const SExpression& sExpressionInit);
private:
    /**
     * Return the stored RSA key.
     *
     * @return S-expression containing the key.
     */
    const SExpression& getSExpressionImpl() const;

    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & sExpression;
    }

    boost::shared_ptr<SExpression> sExpression; /**< S-expression which contains the key. */
};

#endif // RSAKEY_HPP
