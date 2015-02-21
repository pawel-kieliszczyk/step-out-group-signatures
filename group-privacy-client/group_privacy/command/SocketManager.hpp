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
 *
 * The file contains SocketManager class which is responsible
 * for data management that is sent to or received from
 * Group Privacy Server.
 */

#ifndef SOCKETMANAGER_HPP
#define	SOCKETMANAGER_HPP

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <cstring>
#include <string>

/**
 * CheckCommand class.
 *
 * It is responsible for data management that is send to
 * or received from Group Privacy Server.
 */
class SocketManager : private boost::noncopyable
{
public:
    /**
     * Constructor of the CheckCommand class.
     *
     * Creates an instance of the class.
     * @param socket Socket used to comunicate with the Group Privacy Server.
     */
    SocketManager(boost::shared_ptr<boost::asio::ip::tcp::socket> socketInit);

    /**
     * Receives data from Group Privacy Server.
     *
     * @return Data sent from Group Privacy Server.
     */
    std::string receive();

    /**
     * Sends data to Group Privacy Server.
     *
     * @param data Data to send to Group Privacy Server.
     */
    void send(const std::string& data);
private:
    static const std::size_t                          DATA_SIZE;   /**< Maximal size of sending and receiving data. */
    boost::shared_ptr<boost::asio::ip::tcp::socket>   socket;      /**< Socket used to send and receive data. */
};

#endif // SOCKETMANAGER_HPP
