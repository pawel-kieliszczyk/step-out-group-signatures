/**
 * @file Session.hpp
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

#ifndef SESSION_HPP
#define	SESSION_HPP

#include "../command/ICommand.hpp"
#include "../step_out_group_signatures/StepOutGroupSignaturesConstants.hpp"
#include "../step_out_group_signatures/StepOutGroupSignaturesManager.hpp"

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <cstring>
#include <map>
#include <memory>
#include <string>

class Session : public boost::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::io_service& p_service);
    Session(const Session& p_session);
    Session& operator=(const Session& p_session);
    boost::shared_ptr<boost::asio::ip::tcp::socket> getSocket();
    void operator()();
private:
    void registerCommands();
    void run();
    std::string receive();

    std::map<std::string, boost::shared_ptr<ICommand> >   commands;   /**< */
    boost::shared_ptr<boost::asio::ip::tcp::socket>       m_socket;   /**< Socket on which the client is connected. */
};

#endif // SESSION_HPP
