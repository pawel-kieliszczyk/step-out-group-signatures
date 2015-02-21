/**
 * @file Session.cpp
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

#include "Session.hpp"

#include "../command/Commands.hpp"

#include <boost/array.hpp>

Session::Session(boost::asio::io_service& p_service)
    : m_socket(new boost::asio::ip::tcp::socket(p_service))
{
    registerCommands();
}

Session::Session(const Session& p_session)
{
    m_socket = p_session.m_socket;
    registerCommands();
}

Session& Session::operator=(const Session& p_session)
{
    m_socket = p_session.m_socket;
    commands = p_session.commands;
    return *this;
}

boost::shared_ptr<boost::asio::ip::tcp::socket> Session::getSocket()
{
    return m_socket;
}

void Session::operator()()
{
    run();
}

void Session::registerCommands()
{
    commands["check"].reset(new CheckCommand(m_socket));
    commands["close-signature"].reset(new CloseSignatureCommand(m_socket));
    commands["finalize-signature"].reset(new FinalizeSignatureCommand(m_socket));
    commands["get-signature"].reset(new GetSignatureCommand(m_socket));
    commands["initialize-signature"].reset(new InitializeSignatureCommand(m_socket));
    commands["join-signature"].reset(new JoinSignatureCommand(m_socket));
    commands["publish"].reset(new PublishCommand(m_socket));
    commands["quit"].reset(new QuitCommand(m_socket));
    commands["register"].reset(new RegisterCommand(m_socket));
    commands["sign"].reset(new SignCommand(m_socket));
    commands["verify"].reset(new VerifyCommand(m_socket));
}

void Session::run()
{
    try
    {
        std::string command;
        while(command != "quit")
        {
            command = receive();
            if(commands.count(command))
                commands[command]->execute();
            else
                std::cerr << "Wrong command received: " << command << std::endl;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::string Session::receive()
{
    boost::array<char, 512> l_array;
    boost::system::error_code l_error;
    std::size_t l_len = m_socket->read_some(boost::asio::buffer(l_array), l_error);
    return std::string(l_array.c_array(), l_len);
}
