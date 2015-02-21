/**
 * @file SerializationUtils.hpp
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
 * The file contains a class which manages one client's connection.
 */

#ifndef SERIALIZATIONUTILS_HPP
#define	SERIALIZATIONUTILS_HPP

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <sstream>
#include <string>

namespace Utils
{

/**
 * Deserializes objects from string to a given type.
 *
 * @param serialized String containing the serialized object.
 * @return Deserialized object.
 */
template<typename Serializable>
Serializable deserialize(const std::string& serialized)
{
    std::stringstream ss;
    ss << serialized;
    boost::archive::text_iarchive ia(ss);
    Serializable deserialized;
    ia >> deserialized;
    return deserialized;
}

/**
 * Serializes a given object.
 *
 * @param serializable Object to serialize.
 * @return String containing the serialized object.
 */
template<typename Serializable>
std::string serialize(const Serializable& serializable)
{
    std::stringstream ss;
    boost::archive::text_oarchive oa(ss);
    oa << serializable;
    return ss.str();
}

} // namespace Utils

#endif // SERIALIZATIONUTILS_HPP
