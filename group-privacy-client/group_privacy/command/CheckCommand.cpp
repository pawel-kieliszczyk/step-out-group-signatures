/**
 * @file CheckCommand.cpp
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
 * \c CheckCommand class.
 */

#include "CheckCommand.hpp"

#include <boost/lexical_cast.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

CheckCommand::CheckCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesClientManager(StepOutGroupSignaturesClientManager::instance())
{
}

Signature CheckCommand::determineSignature() throw(std::runtime_error)
{
    std::string signatureFilename;
    std::cin >> signatureFilename;
    if(!fileExists(signatureFilename))
        throw std::runtime_error("File \'" + signatureFilename + "\' doesn't exist!");
    return Utils::deserialize<Signature>(getFileContent(signatureFilename));
}

unsigned int CheckCommand::determineUserIndex()
{
    unsigned int userIndex;
    std::cin >> userIndex;
    return userIndex;
}

void CheckCommand::execute()
{
    std::cout << "CheckCommand::execute() started" << std::endl;
    try
    {
        Signature signature = determineSignature();
        unsigned int userIndex = determineUserIndex();
        send(std::string("check"));
        receive<std::string>(); // OK status
        send(stepOutGroupSignaturesClientManager.createCheckProcedureInput(userIndex, signature));
        if(receive<std::string>() == "yes")
        {
            send(std::string("ok"));
            UserPublicKey userPublicKey = receive<UserPublicKey>();
            send(std::string("ok"));
            PublishedValues publishedValues = receive<PublishedValues>();
            checkUser(userIndex, userPublicKey, publishedValues, signature);
        }
        else
        {
            std::cout << "User " << userIndex << " hasn't published necessary data." << std::endl;
            std::cout << "It is unknown whether he is an author of the signature." << std::endl;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "CheckCommand::execute() finished" << std::endl;

//    std::cout << "CheckCommand::execute() started" << std::endl;
//    std::string signatureFilename;
//    std::cin >> signatureFilename;
//    if(!fileExists(signatureFilename))
//    {
//        std::cerr << "File \'" << signatureFilename << "\' doesn't exist!" << std::endl;
//        return;
//    }
//    std::string serializedSignature = getFileContent(signatureFilename);
//    Signature signature = Utils::deserialize<Signature>(serializedSignature);
//    unsigned int userIndex;
//    std::cin >> userIndex;
//    socketManager.send("check");
//    socketManager.receive(); // OK status
//    CheckProcedureInput checkProcedureInput =
//        stepOutGroupSignaturesClientManager.createCheckProcedureInput(userIndex, signature);
//    std::string serializedCheckProcedureInput = Utils::serialize(checkProcedureInput);
//    socketManager.send(serializedCheckProcedureInput);
//    std::string hasPublishedValues = socketManager.receive();
//    if(hasPublishedValues == "yes")
//    {
//        std::cout << "User " << userIndex << " has published necessary data." << std::endl;
//        socketManager.send("ok");
//        std::string serializedUserPublicKey = socketManager.receive();
//        UserPublicKey userPublicKey = Utils::deserialize<UserPublicKey>(serializedUserPublicKey);
//        socketManager.send("ok");
//        std::string serializedPublishedValues = socketManager.receive();
//        PublishedValues publishedValues = Utils::deserialize<PublishedValues>(serializedPublishedValues);
//        if(stepOutGroupSignaturesClientManager.isSigner(userPublicKey, publishedValues, signature))
//            std::cout << "He is an author of the signature." << std::endl;
//        else if(stepOutGroupSignaturesClientManager.isNotSigner(userPublicKey, publishedValues, signature))
//            std::cout << "He is not an author of the signature." << std::endl;
//        else
//            std::cout << "However he probably cheats because the data is not real." << std::endl;
//    }
//    else
//    {
//        std::cout << "User " << userIndex << " hasn't published necessary data." << std::endl;
//        std::cout << "It is unknown whether he is an author of the signature." << std::endl;
//    }
//    std::cout << "CheckCommand::execute() finished" << std::endl;
}

bool CheckCommand::fileExists(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    return file.is_open();
}

std::string CheckCommand::getFileContent(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

void CheckCommand::checkUser(const unsigned int userIndex,
                             const UserPublicKey& userPublicKey,
                             const PublishedValues& publishedValues,
                             const Signature& signature)
{
    std::cout << "User " << userIndex << " has published necessary data." << std::endl;
    if(stepOutGroupSignaturesClientManager.isSigner(userPublicKey, publishedValues, signature))
        std::cout << "He is an author of the signature." << std::endl;
    else if(stepOutGroupSignaturesClientManager.isNotSigner(userPublicKey, publishedValues, signature))
        std::cout << "He is not an author of the signature." << std::endl;
    else
        std::cout << "However he probably cheats because the data is not real." << std::endl;
}
