/**
 * @file PublishCommand.cpp
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
 * The file contains definitions of the methods from
 * \c PublishCommand class.
 */

#include "PublishCommand.hpp"

#include "../step_out_group_signatures/PublishProcedureInput.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

PublishCommand::PublishCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesClientManager(StepOutGroupSignaturesClientManager::instance())
{
}

Signature PublishCommand::determineSignature() throw(std::runtime_error)
{
    std::string signatureFilename;
    std::cin >> signatureFilename;
    if(!fileExists(signatureFilename))
        throw std::runtime_error("File \'" + signatureFilename + "\' doesn't exist!");
    return Utils::deserialize<Signature>(getFileContent(signatureFilename));
}

void PublishCommand::execute()
{
    std::cout << "PublishCommand::execute() started" << std::endl;
    try
    {
        Signature signature = determineSignature();
        send(std::string("publish"));
        receive<std::string>(); // OK status
        send(stepOutGroupSignaturesClientManager.createPublishProcedureInput(signature));
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "PublishCommand::execute() finished" << std::endl;

//    std::cout << "PublishCommand::execute() started" << std::endl;
//    std::string signatureFilename;
//    std::cin >> signatureFilename;
//    if(!fileExists(signatureFilename))
//    {
//        std::cerr << "File \'" << signatureFilename << "\' doesn't exist!" << std::endl;
//        return;
//    }
//    std::string serializedSignature = getFileContent(signatureFilename);
//    Signature signature = Utils::deserialize<Signature>(serializedSignature);
//    socketManager.send("publish");
//    socketManager.receive(); // OK status
//    PublishProcedureInput publishProcedureInput =
//        stepOutGroupSignaturesClientManager.createPublishProcedureInput(signature);
//    std::string serializedPublishProcedureInput = Utils::serialize(publishProcedureInput);
//    socketManager.send(serializedPublishProcedureInput);
//    std::cout << "PublishCommand::execute() finished" << std::endl;
}

bool PublishCommand::fileExists(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    return file.is_open();
}

std::string PublishCommand::getFileContent(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}