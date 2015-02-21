/**
 * @file GroupPrivacyServerManager.cpp
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

#include "GroupPrivacyServerManager.hpp"

#include <boost/bind.hpp>
#include <boost/thread.hpp>

GroupPrivacyServerManager::GroupPrivacyServerManager(boost::asio::io_service& p_service, const int p_port)
    : m_acceptor(p_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), p_port)),
      m_service(p_service)
{
    prepareNewSession();
}

void GroupPrivacyServerManager::prepareNewSession()
{
    boost::shared_ptr<Session> l_newSession(new Session(m_service));
    m_acceptor.async_accept(*l_newSession->getSocket(),
                            boost::bind(&GroupPrivacyServerManager::handleConnection,
                                        this,
                                        l_newSession,
                                        boost::asio::placeholders::error));
}

void GroupPrivacyServerManager::handleConnection(boost::shared_ptr<Session> p_session,
                                                 const boost::system::error_code& p_error)
{
    if(!p_error)
    {
        createSessionThread(p_session);
        prepareNewSession();
    }
}

void GroupPrivacyServerManager::createSessionThread(boost::shared_ptr<Session> p_session)
{
    boost::thread l_sessionThread(*p_session);
}
