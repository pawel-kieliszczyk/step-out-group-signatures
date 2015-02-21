/**
 * @file GroupPrivacyClientManager.hpp
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
 * This file containg GroupPrivacyClientManager class
 * which is responsilbe for creating a connection with
 * the Group Privacy Server.
 */

#ifndef GROUPPRIVACYCLIENTMANAGER_HPP
#define	GROUPPRIVACYCLIENTMANAGER_HPP

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <string>

/**
 * GroupPrivacyClientManager class.
 *
 * It is responsilbe for creating a connection
 * with the Group Privacy Server.
 */
class GroupPrivacyClientManager : private boost::noncopyable
{
public:
    /**
     * Constructor of the GroupPrivacyClientManager class.
     *
     * @param host A host to connect to.
     * @param port A server's port to connect.
     */
    GroupPrivacyClientManager(const std::string& host, const std::string& port);

    /**
     * Initializes and sets up the connection
     * with the Group Privacy Server.
     */
    void manage();
private:
    /**
     * Connects to the Group Privacy Server.
     *
     * @param host A host to connect to.
     * @param port A server's port to connect.
     */
    void connectToServer(const std::string& host, const std::string& port);

    boost::shared_ptr<boost::asio::ip::tcp::socket> socket; /**< Socket used to comunicate with the Group Privacy Server. */
};

#endif // GROUPPRIVACYCLIENTMANAGER_HPP
