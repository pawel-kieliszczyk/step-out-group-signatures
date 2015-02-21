/**
 * @file FinalizeSignatureOutput.hpp
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

#ifndef FINALIZESIGNATUREOUTPUT_HPP
#define	FINALIZESIGNATUREOUTPUT_HPP

#include "../step_out_group_signatures/ThetaPrim.hpp"

#include <boost/serialization/access.hpp>
#include <boost/tuple/tuple.hpp>

class FinalizeSignatureOutput : public boost::tuple<unsigned int, ThetaPrimElement>
{
    friend class boost::serialization::access;
public:
    FinalizeSignatureOutput();
    FinalizeSignatureOutput(const unsigned int userIndex, const ThetaPrimElement& thetaPrimElement);
    FinalizeSignatureOutput(const FinalizeSignatureOutput& output);
    FinalizeSignatureOutput operator=(const FinalizeSignatureOutput& output);
    const unsigned int& getUserIndex() const;
    unsigned int& getUserIndex();
    const ThetaPrimElement& getThetaPrimElement() const;
    ThetaPrimElement& getThetaPrimElement();
private:
    template<typename Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & getUserIndex();
        archive & getThetaPrimElement();
    }
};

#endif // FINALIZESIGNATUREOUTPUT_HPP
