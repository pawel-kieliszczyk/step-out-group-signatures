/**
 * @file DigitalSignature.hpp
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
 * The file contains DigitalSignature class which is
 * a wrapper for digital signatures stored as s-expressions.
 */

#ifndef DIGITALSIGNATURE_HPP
#define	DIGITALSIGNATURE_HPP

#include "../s_expression/SExpression.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/shared_ptr.hpp>

/**
 * DigitalSignature class.
 *
 * It is a wrapper for digital
 * signatures stored as s-expressions.
 */
class DigitalSignature
{
    friend class boost::serialization::access;
public:
    /**
     * Default constructor of the DigitalSignature class.
     *
     * Creates an instance of the class.
     */
    DigitalSignature();

    /**
     * Constructor of the DigitalSignature class.
     *
     * Creates an instance of the class based on the given s-expression.
     *
     * @param sExpressionInit S-expression storing a digital signature.
     */
    DigitalSignature(const SExpression& sExpressionInit);

    /**
     * Copy constructor of the DigitalSignature class.
     *
     * @param digitalSignature Instance of the class to be copied.
     */
    DigitalSignature(const DigitalSignature& digitalSignature);

    /**
     * Assigns the given signature to the class instance.
     *
     * @param digitalSignature Instance of the class to be copied.
     *
     * @return Reference to the instance of the class.
     */
    DigitalSignature& operator=(const DigitalSignature& digitalSignature);

    /**
     * Returns s-expression of a digital sitnature.
     *
     * @return S-expression containing a digital signature.
     */
    const SExpression& getSExpression() const;
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & sExpression;
    }

    boost::shared_ptr<SExpression> sExpression;
};

#endif // DIGITALSIGNATURE_HPP
