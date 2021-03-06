/**
 * @file PublishProcedureInput.cpp
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

#include "PublishProcedureInput.hpp"

PublishProcedureInput::PublishProcedureInput()
    : boost::tuple<unsigned int, PublishedValues>()
{
}

PublishProcedureInput::PublishProcedureInput(const unsigned int userIndex, const PublishedValues& publishedValues)
    : boost::tuple<unsigned int, PublishedValues>(userIndex, publishedValues)
{
}

PublishProcedureInput::PublishProcedureInput(const PublishProcedureInput& input)
    : boost::tuple<unsigned int, PublishedValues>(input)
{
}

PublishProcedureInput PublishProcedureInput::operator=(const PublishProcedureInput& input)
{
    boost::tuple<unsigned int, PublishedValues>::operator=(input);
    return *this;
}

const unsigned int& PublishProcedureInput::getUserIndex() const
{
    return boost::get<0>(*this);
}

unsigned int& PublishProcedureInput::getUserIndex()
{
    return boost::get<0>(*this);
}

const PublishedValues& PublishProcedureInput::getPublishedValues() const
{
    return boost::get<1>(*this);
}

PublishedValues& PublishProcedureInput::getPublishedValues()
{
    return boost::get<1>(*this);
}
