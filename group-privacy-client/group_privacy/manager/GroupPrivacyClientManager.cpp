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
 */

#include "GroupPrivacyClientManager.hpp"
#include "Session.hpp"

GroupPrivacyClientManager::GroupPrivacyClientManager(const std::string& host, const std::string& port)
    : socket()
{
    connectToServer(host, port);
}

void GroupPrivacyClientManager::connectToServer(const std::string& host, const std::string& port)
{
    using boost::asio::ip::tcp;
    boost::asio::io_service service;
    tcp::resolver resolver(service);
    tcp::resolver::query query(host, port);
    tcp::resolver::iterator endpointIterator = resolver.resolve(query);
    tcp::resolver::iterator end;
    socket.reset(new tcp::socket(service));
    boost::system::error_code error = boost::asio::error::host_not_found;
    while(error && endpointIterator != end)
    {
        socket->close();
        socket->connect(*endpointIterator++, error);
    }
    if(error)
        throw boost::system::system_error(error);
}

void GroupPrivacyClientManager::manage()
{
    Session session(socket);
    session.run();
}
