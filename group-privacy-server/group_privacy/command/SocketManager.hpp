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

#ifndef SOCKETMANAGER_HPP
#define	SOCKETMANAGER_HPP

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <cstring>
#include <string>

class SocketManager : private boost::noncopyable
{
public:
    SocketManager(boost::shared_ptr<boost::asio::ip::tcp::socket> socketInit);
    std::string receive();
    void send(const std::string& data);
private:
    static const std::size_t                          DATA_SIZE;   /**< Maximal size of sending and receiving data. */
    boost::shared_ptr<boost::asio::ip::tcp::socket>   socket;      /**< Socket used to send and receive data. */
};

#endif // SOCKETMANAGER_HPP
