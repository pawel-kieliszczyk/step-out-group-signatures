/**
 * @file SignCommand.cpp
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
 * \c SignCommand class.
 */

#include "SignCommand.hpp"

#include "../step_out_group_signatures/Signature.hpp"
#include "../step_out_group_signatures/SignProcedureInput.hpp"
#include "../step_out_group_signatures/SignProcedureOutput.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

SignCommand::SignCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesClientManager(StepOutGroupSignaturesClientManager::instance())
{
}

boost::tuple<std::string, std::string> SignCommand::determineMessage() throw(std::runtime_error)
{
    std::string messageFilename;
    std::cin >> messageFilename;
    if(!fileExists(messageFilename))
        throw std::runtime_error("File \'" + messageFilename + "\' doesn't exist!");
    return boost::tuple<std::string, std::string>(messageFilename, getFileContent(messageFilename));
}

void SignCommand::execute()
{
    std::cout << "SignCommand::execute() started" << std::endl;
    try
    {
        boost::tuple<std::string, std::string> message = determineMessage();
        send(std::string("sign"));
        receive<std::string>(); // OK status
        const SignProcedureInput input =
            stepOutGroupSignaturesClientManager.createSignProcedureInput(boost::get<1>(message));
        send(input);
        SignProcedureOutput output = receive<SignProcedureOutput>();
        saveSignature(boost::get<0>(message), stepOutGroupSignaturesClientManager.createSignature(input, output));
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "SignCommand::execute() finished" << std::endl;

//    std::cout << "SignCommand::execute() started" << std::endl;
//    std::string filename = getFilename();
//    if(!fileExists(filename))
//    {
//        std::cerr << "File \'" << filename << "\' doesn't exist!" << std::endl;
//        return;
//    }
//    std::string messageToSign = getFileContent(filename);
//    socketManager.send("sign");
//    socketManager.receive(); // OK status
//    const SignProcedureInput input = stepOutGroupSignaturesClientManager.createSignProcedureInput(messageToSign);
//    std::string serializedInput = Utils::serialize(input);
//    socketManager.send(serializedInput);
//    std::string serializedOutput = socketManager.receive();
//    SignProcedureOutput output = Utils::deserialize<SignProcedureOutput>(serializedOutput);
//    Signature signature = stepOutGroupSignaturesClientManager.createSignature(input, output);
//    saveSignature(filename, signature);
//    std::cout << "SignCommand::execute() finished" << std::endl;
}

bool SignCommand::fileExists(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    return file.is_open();
}

std::string SignCommand::getFileContent(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

std::string SignCommand::getFilename()
{
    std::string filename;
    std::cin >> filename;
    return filename;
}

void SignCommand::saveSignature(const std::string& filename, const Signature& signature)
{
    const std::string signatureFilename = filename + ".sig";
    std::ofstream file(signatureFilename.c_str());
    file << Utils::serialize(signature);
}
