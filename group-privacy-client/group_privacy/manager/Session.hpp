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

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

/**
 * Session class.
 *
 * It manages a client's connection.
 */
class Session
{
public:
    /**
     * Constructor of the Session class.
     *
     * Creates an instance of the class.
     *
     * @param socket Socket used to comunicate with the Group Privacy Server.
     */
    Session(boost::shared_ptr<boost::asio::ip::tcp::socket> socketInit);

    /**
     * Copy constructor of the Session class.
     *
     * @param session A \c Session object to be copied.
     */
    Session(const Session& session);

    /**
     * Assigns a given session to the instance of the class.
     *
     * @param session A \c Session object to be copied.
     *
     * @return Reference to the object of the class.
     */
    Session& operator=(const Session& session);

    /**
     * The main method of the class.
     * It awaits for users commands and invokes proper
     * classed that suppert them.
     */
    void run();
private:

    /**
     * Registers all command that a user can invoke.
     */
    void registerCommands();

    std::map<std::string, boost::shared_ptr<ICommand> >   commands;   /**< Container for all possible commands. */
    boost::shared_ptr<boost::asio::ip::tcp::socket>       socket;     /**< Socket used to comunicate with the Group Privacy Server. */
};

#endif // SESSION_HPP
