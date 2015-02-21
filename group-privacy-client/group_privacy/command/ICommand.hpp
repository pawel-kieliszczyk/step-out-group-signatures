/**
 * @file ICommand.hpp
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
 * The file contains ICommand class which is an interface
 * for all classes responsible for interaction between
 * a user and the system.
 */

#ifndef ICOMMAND_HPP
#define	ICOMMAND_HPP

#include "SerializationUtils.hpp"
#include "SocketManager.hpp"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

/**
 * ICommand class.
 *
 * Creates an interface for all classes responsible
 * for interaction between a user and the system.
 */
class ICommand
{
public:
    /**
     * Constructor of the ICommand class.
     *
     * @param socket Socket used to comunicate with the Group Privacy Server.
     */
    ICommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

    /**
     * Virtual destructor of the ICommand class.
     */
    virtual ~ICommand() {}

    /**
     * Pure virtual method which has to be implemented
     * by all inheriting classes.
     */
    virtual void execute() = 0;
protected:
    /**
     * Receives data from Group Privacy Server.
     *
     * @return Object sent from Group Privacy Server.
     */
    template<typename Serializable>
    Serializable receive();

    /**
     * Sends data to Group Privacy Server.
     *
     * @param serializable Object to send to Group Privacy Server.
     */
    template<typename Serializable>
    void send(const Serializable& serializable);
private:
    SocketManager socketManager; /**< Manager used to send and receive data. */
};

inline ICommand::ICommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : socketManager(socket)
{
}

template<typename Serializable>
Serializable ICommand::receive()
{
    std::string serialized = socketManager.receive();
    return Utils::deserialize<Serializable>(serialized);
}

template<>
inline std::string ICommand::receive<std::string>()
{
    return socketManager.receive();
}

template<typename Serializable>
void ICommand::send(const Serializable& serializable)
{
    std::string serialized = Utils::serialize(serializable);
    socketManager.send(serialized);
}

template<>
inline void ICommand::send<std::string>(const std::string& str)
{
    socketManager.send(str);
}

#endif // ICOMMAND_HPP
