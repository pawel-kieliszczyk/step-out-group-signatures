/**
 * @file Signature.hpp
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

#ifndef SIGNATURE_HPP
#define	SIGNATURE_HPP

#include "../mpi/BigInteger.hpp"
#include "C.hpp"
#include "Delta.hpp"
#include "Sigma.hpp"
#include "ThetaPrim.hpp"

#include <boost/serialization/access.hpp>
#include <boost/tuple/tuple.hpp>

class Signature : public boost::tuple<BigInteger, BigInteger, Delta, ThetaPrim, C, Sigma>
{
    friend class boost::serialization::access;
public:
    Signature();
    Signature(const Signature& signature);
    Signature(const BigInteger&   t,
              const BigInteger&   x,
              const Delta&        delta,
              const ThetaPrim     thetaPrim,
              const C&            c,
              const Sigma&        sigma);
    Signature& operator=(const Signature& signature);
    const BigInteger& getT() const;
    BigInteger& getT();
    const BigInteger& getX() const;
    BigInteger& getX();
    const Delta& getDelta() const;
    Delta& getDelta();
    const ThetaPrim& getThetaPrim() const;
    ThetaPrim& getThetaPrim();
    const C& getC() const;
    C& getC();
    const Sigma& getSigma() const;
    Sigma& getSigma();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & getT();
        archive & getX();
        archive & getDelta();
        archive & getThetaPrim();
        archive & getC();
        archive & getSigma();
    }
};

#endif // SIGNATURE_HPP
