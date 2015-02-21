/**
 * @file VerifyCommand.cpp
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
 * \c VerifyCommand class.
 */

#include "VerifyCommand.hpp"

#include "../key/RSAKey.hpp"
#include "../step_out_group_signatures/GroupZpValues.hpp"
#include "../step_out_group_signatures/Signature.hpp"
#include "../step_out_group_signatures/UserPrivateKey.hpp"

#include <fstream>
#include <iostream>
#include <string>

VerifyCommand::VerifyCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesClientManager(StepOutGroupSignaturesClientManager::instance())
{
}

std::string VerifyCommand::determineMessage() throw(std::runtime_error)
{
    std::string filename;
    std::cin >> filename;
    if(!fileExists(filename))
        throw std::runtime_error("File \'" + filename + "\' doesn't exist!");
    return getFileContent(filename);
}

Signature VerifyCommand::determineSignature() throw(std::runtime_error)
{
    std::string filename;
    std::cin >> filename;
    if(!fileExists(filename))
        throw std::runtime_error("File \'" + filename + "\' doesn't exist!");
    return Utils::deserialize<Signature>(getFileContent(filename));
}

void VerifyCommand::execute()
{
    std::cout << "VerifyCommand::execute() started" << std::endl;
    try
    {
        std::string message = determineMessage();
        Signature signature = determineSignature();
        send(std::string("verify"));
        stepOutGroupSignaturesClientManager.setGroupZpValues(receive<GroupZpValues>());
        send(std::string("ok"));
        stepOutGroupSignaturesClientManager.setServerPublicKey(receive<RSAKey>());
        send(std::string("ok"));
        stepOutGroupSignaturesClientManager.setDummyUserPrivateKey(receive<UserPrivateKey>());
        if(stepOutGroupSignaturesClientManager.verifySignature(message, signature))
            std::cout << "Signature is valid." << std::endl;
        else
            std::cout << "Signature is not valid." << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "VerifyCommand::execute() finished" << std::endl;

//    std::cout << "VerifyCommand::execute() started" << std::endl;
//    std::string filename;
//    std::cin >> filename;
//    std::string signatureFilename;
//    std::cin >> signatureFilename;
//    if(!fileExists(filename))
//    {
//        std::cerr << "File \'" << filename << "\' doesn't exist!" << std::endl;
//        return;
//    }
//    if(!fileExists(signatureFilename))
//    {
//        std::cerr << "File \'" << signatureFilename << "\' doesn't exist!" << std::endl;
//        return;
//    }
//    std::string message = getFileContent(filename);
//    std::string serializedSignature = getFileContent(signatureFilename);
//    Signature signature = Utils::deserialize<Signature>(serializedSignature);
//    socketManager.send("verify");
//    std::string serializedGroupZpValues = socketManager.receive();
//    GroupZpValues groupZpValues = Utils::deserialize<GroupZpValues>(serializedGroupZpValues);
//    stepOutGroupSignaturesClientManager.setGroupZpValues(groupZpValues);
//    socketManager.send("ok");
//    std::string serializedServerPublicKey = socketManager.receive();
//    RSAKey serverPublicKey = Utils::deserialize<RSAKey>(serializedServerPublicKey);
//    stepOutGroupSignaturesClientManager.setServerPublicKey(serverPublicKey);
//    socketManager.send("ok");
//    std::string serializedDummyUserPrivateKey = socketManager.receive();
//    UserPrivateKey dummyUserPrivateKey = Utils::deserialize<UserPrivateKey>(serializedDummyUserPrivateKey);
//    stepOutGroupSignaturesClientManager.setDummyUserPrivateKey(dummyUserPrivateKey);
//    if(stepOutGroupSignaturesClientManager.verifySignature(message, signature))
//        std::cout << "Signature is valid." << std::endl;
//    else
//        std::cout << "Signature is not valid." << std::endl;
//    std::cout << "VerifyCommand::execute() finished" << std::endl;
}

bool VerifyCommand::fileExists(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    return file.is_open();
}

std::string VerifyCommand::getFileContent(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}
