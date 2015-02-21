/**
 * @file SocketManager.hpp
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

#include "SocketManager.hpp"

#include <boost/assert.hpp>

const std::size_t SocketManager::DATA_SIZE = 65536;

SocketManager::SocketManager(boost::shared_ptr<boost::asio::ip::tcp::socket> socketInit)
    : socket(socketInit)
{
}

std::string SocketManager::receive()
{
    boost::array<char, DATA_SIZE> buffer;
    boost::system::error_code error;
    std::size_t length = socket->read_some(boost::asio::buffer(buffer), error);
    BOOST_ASSERT(length < DATA_SIZE);
    return std::string(buffer.c_array(), length);
}

void SocketManager::send(const std::string& data)
{
    BOOST_ASSERT(data.size() < DATA_SIZE);
    socket->write_some(boost::asio::buffer(data));
}
