/**
 * @file DigitalSignature.cpp
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

#include "DigitalSignature.hpp"

#include <boost/assert.hpp>

DigitalSignature::DigitalSignature()
    : sExpression()
{
}

DigitalSignature::DigitalSignature(const SExpression& sExpressionInit)
    : sExpression(new SExpression(sExpressionInit))
{
}

DigitalSignature::DigitalSignature(const DigitalSignature& digitalSignature)
    : sExpression(digitalSignature.sExpression)
{
}

DigitalSignature& DigitalSignature::operator=(const DigitalSignature& digitalSignature)
{
    sExpression = digitalSignature.sExpression;
    return *this;
}

const SExpression& DigitalSignature::getSExpression() const
{
    BOOST_ASSERT(sExpression);
    return *sExpression;
}
