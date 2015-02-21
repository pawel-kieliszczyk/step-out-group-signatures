/**
 * @file Psi.cpp
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

#include "Psi.hpp"

PsiElement::PsiElement()
    : boost::tuple<BigInteger, BigInteger>()
{
}

PsiElement::PsiElement(const BigInteger& first, const BigInteger& second)
    : boost::tuple<BigInteger, BigInteger>(first, second)
{
}

PsiElement::PsiElement(const PsiElement& element)
    : boost::tuple<BigInteger, BigInteger>(element)
{
}

PsiElement& PsiElement::operator=(const PsiElement& element)
{
    boost::tuple<BigInteger, BigInteger>::operator=(element);
    return *this;
}


Psi::Psi() : std::vector<PsiElement>()
{
}

Psi::Psi(const Psi& psi)
    : std::vector<PsiElement>(psi)
{
}

Psi& Psi::operator=(const Psi& psi)
{
    std::vector<PsiElement>::operator=(psi);
    return *this;
}

bool operator<(const PsiElement& left, const PsiElement& right)
{
    if(boost::get<0>(left) < boost::get<0>(right))
        return true;
    if(boost::get<0>(left) == boost::get<0>(right) && boost::get<1>(left) < boost::get<1>(right))
        return true;
    return false;
}
