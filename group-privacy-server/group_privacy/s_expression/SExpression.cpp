/**
 * @file SExpression.cpp
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

#include "SExpression.hpp"

#include <boost/assert.hpp>

#include <cstring>

SExpression::SExpression()
{
    const int AUTODETECT = 1;
    gcry_error_t error = gcry_sexp_new(&sExp, "()", 2, AUTODETECT);
    BOOST_ASSERT(!error);
}

SExpression::SExpression(gcry_sexp_t sExpInit) : sExp(sExpInit)
{
}

SExpression::SExpression(const SExpression& sExpression)
{
    copySExp(sExpression.sExp);
}

SExpression& SExpression::operator=(const SExpression& sExpression)
{
    releaseSExp();
    copySExp(sExpression.sExp);
    return *this;
}

SExpression::~SExpression()
{
    releaseSExp();
}

void SExpression::copySExp(gcry_sexp_t sExpToCopy)
{
    std::size_t sExpLength = getSExpLength(sExpToCopy);
    char* sExpBuffer = new char[sExpLength];
    std::size_t error = gcry_sexp_sprint(sExpToCopy, GCRYSEXP_FMT_DEFAULT, sExpBuffer, sExpLength);
    BOOST_ASSERT(error != 0);
    const int AUTODETECT = 1;
    gcry_sexp_new(&sExp, sExpBuffer, sExpLength, AUTODETECT);
    delete[] sExpBuffer;
}

gcry_sexp_t SExpression::get() const
{
    return sExp;
}

std::size_t SExpression::getSExpLength(gcry_sexp_t sExp) const
{
    return gcry_sexp_sprint(sExp, GCRYSEXP_FMT_DEFAULT, NULL, 0);
}

void SExpression::releaseSExp()
{
    gcry_sexp_release(sExp);
}
