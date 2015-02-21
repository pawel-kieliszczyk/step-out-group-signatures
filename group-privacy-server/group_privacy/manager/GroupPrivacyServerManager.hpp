/**
 * @file GroupPrivacyServerManager.hpp
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
 * The file contains a class that handles new connections
 * and manages client's sessions.
 */

#ifndef GROUPPRIVACYSERVERMANAGER_HPP
#define	GROUPPRIVACYSERVERMANAGER_HPP

#include "Session.hpp"

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

/**
 * A GroupPrivacyServerManager class.
 * Handles new connections and manages clients' sessions.
 */
class GroupPrivacyServerManager : private boost::noncopyable
{
public:
    /**
     * Constructor of GroupPrivacyServerManger class.
     *
     * Initializes all resources and invokes preparation
     * of a new client's connection.
     *
     * @param p_service Service that provides data flow during a session.
     * @param p_port Connection port.
     */
    GroupPrivacyServerManager(boost::asio::io_service& p_service, const int p_port);
private:
    /**
     * Prepares a new client's connection.
     */
    void prepareNewSession();

    /**
     * Handles a client's connection to the server by invoking
     * creation of a new thread for the given session.
     * At the end triggers preparation of a new session.
     *
     * @param p_session A session to start.
     * @param p_error Error identifier. Should be 0 if there were no errors.
     */
    void handleConnection(boost::shared_ptr<Session> p_session, const boost::system::error_code& p_error);

    /**
     * Creates a new thread for the given client's session.
     *
     * @param p_session Client's session.
     */
    void createSessionThread(boost::shared_ptr<Session> p_session);

    boost::asio::ip::tcp::acceptor   m_acceptor;   /**< Acceptor that enables new connections. */
    boost::asio::io_service&         m_service;    /**< Service needed to create sockets. */
};

#endif // GROUPPRIVACYSERVERMANAGER_HPP
