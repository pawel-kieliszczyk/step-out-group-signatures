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

#include <iostream>

Session::Session(boost::shared_ptr<boost::asio::ip::tcp::socket> socketInit)
    : socket(socketInit)
{
    registerCommands();
}

Session::Session(const Session& session)
    : commands(session.commands),
      socket(session.socket)
{
}

Session& Session::operator=(const Session& session)
{
    commands = session.commands;
    socket = session.socket;
    return *this;
}

void Session::registerCommands()
{
    commands["check"].reset(new CheckCommand(socket));
    commands["close-signature"].reset(new CloseSignatureCommand(socket));
    commands["finalize-signature"].reset(new FinalizeSignatureCommand(socket));
    commands["get-signature"].reset(new GetSignatureCommand(socket));
    commands["initialize-signature"].reset(new InitializeSignatureCommand(socket));
    commands["join-signature"].reset(new JoinSignatureCommand(socket));
    commands["publish"].reset(new PublishCommand(socket));
    commands["quit"].reset(new QuitCommand(socket));
    commands["register"].reset(new RegisterCommand(socket));
    commands["sign"].reset(new SignCommand(socket));
    commands["verify"].reset(new VerifyCommand(socket));
}

void Session::run()
{
    StepOutGroupSignaturesClientManager& stepOutGroupSignaturesClientManager =
        StepOutGroupSignaturesClientManager::instance();
    std::string command;
    while(command != "quit")
    {
        std::cout << "[" << stepOutGroupSignaturesClientManager.getUserIndex() << "] > ";
        std::cin >> command;
        if(commands.count(command))
            commands[command]->execute();
        else
            std::cerr << "Unknown command: " << command << std::endl;
    }
    socket->close();
}
