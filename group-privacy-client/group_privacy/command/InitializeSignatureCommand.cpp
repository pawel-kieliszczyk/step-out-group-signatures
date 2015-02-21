/**
 * @file InitializeSignatureCommand.cpp
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

#include "InitializeSignatureCommand.hpp"

#include "../step_out_group_signatures/InitializeSignatureInput.hpp"

#include <boost/lexical_cast.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

InitializeSignatureCommand::InitializeSignatureCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesClientManager(StepOutGroupSignaturesClientManager::instance())
{
}

boost::tuple<std::string, std::string> InitializeSignatureCommand::determineMessage() throw(std::runtime_error)
{
    std::string messageFilename;
    std::cin >> messageFilename;
    if(!fileExists(messageFilename))
        throw std::runtime_error("File \'" + messageFilename + "\' doesn't exist!");
    return boost::tuple<std::string, std::string>(messageFilename, getFileContent(messageFilename));
}

void InitializeSignatureCommand::execute()
{
    std::cout << "InitializeSignatureCommand::execute() started" << std::endl;
    try
    {
        boost::tuple<std::string, std::string> message = determineMessage();
        send(std::string("initialize-signature"));
        receive<std::string>(); // OK status
        send(stepOutGroupSignaturesClientManager.createInitializeSignatureInput(boost::get<1>(message)));
        unsigned int signatureIndex = boost::lexical_cast<unsigned int>(receive<std::string>());
        std::cout << "Assigned unique signature's number is " << signatureIndex << "." << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "InitializeSignatureCommand::execute() finished" << std::endl;
}

bool InitializeSignatureCommand::fileExists(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    return file.is_open();
}

std::string InitializeSignatureCommand::getFileContent(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}
