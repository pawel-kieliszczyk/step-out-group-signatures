/**
 * @file SigProcedureOutput.hpp
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

#ifndef SIGNPROCEDUREOUTPUT_HPP
#define	SIGNPROCEDUREOUTPUT_HPP

#include "C.hpp"
#include "Delta.hpp"
#include "Sigma.hpp"

#include <boost/serialization/access.hpp>
#include <boost/tuple/tuple.hpp>

class SignProcedureOutput : public boost::tuple<Delta, C, Sigma>
{
    friend class boost::serialization::access;
public:
    SignProcedureOutput();
    SignProcedureOutput(const Delta& delta, const C& c, const Sigma& sigma);
    SignProcedureOutput(const SignProcedureOutput& output);
    SignProcedureOutput& operator=(const SignProcedureOutput& output);
    const Delta& getDelta() const;
    Delta& getDelta();
    const C& getC() const;
    C& getC();
    const Sigma& getSigma() const;
    Sigma& getSigma();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & getDelta();
        archive & getC();
        archive & getSigma();
    }
};

#endif // SIGNPROCEDUREOUTPUT_HPP
