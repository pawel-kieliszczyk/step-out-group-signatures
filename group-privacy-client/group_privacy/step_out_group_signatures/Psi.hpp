/**
 * @file Psi.hpp
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

#ifndef PSI_HPP
#define	PSI_HPP

#include "../mpi/BigInteger.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/tuple/tuple.hpp>

#include <vector>

class PsiElement : public boost::tuple<BigInteger, BigInteger>
{
    friend class boost::serialization::access;
public:
    PsiElement();
    PsiElement(const BigInteger& first, const BigInteger& second);
    PsiElement(const PsiElement& element);
    PsiElement& operator=(const PsiElement& element);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & boost::get<0>(*this);
        archive & boost::get<1>(*this);
    }
};

class Psi : public std::vector<PsiElement>
{
    friend class boost::serialization::access;
public:
    Psi();
    Psi(const Psi& psi);
    Psi& operator=(const Psi& psi);
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & dynamic_cast<std::vector<PsiElement>&>(*this);
    }
};

bool operator<(const PsiElement& left, const PsiElement& right);

#endif // PSI_HPP
