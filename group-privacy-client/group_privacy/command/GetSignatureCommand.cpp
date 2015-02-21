/**
 * @file GetSignatureCommand.cpp
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

#include "GetSignatureCommand.hpp"

#include "../step_out_group_signatures/Signature.hpp"
#include "SerializationUtils.hpp"

#include <boost/lexical_cast.hpp>

#include <fstream>
#include <iostream>
#include <string>

GetSignatureCommand::GetSignatureCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesClientManager(StepOutGroupSignaturesClientManager::instance())
{
}

std::string GetSignatureCommand::determineSignatureFilename()
{
    std::string signatureFilename;
    std::cin >> signatureFilename;
    return signatureFilename;
}

unsigned int GetSignatureCommand::determineSignatureIndex()
{
    unsigned int signatureIndex;
    std::cin >> signatureIndex;
    return signatureIndex;
}

void GetSignatureCommand::saveSignature(const std::string& filename, const Signature& signature)
{
    std::ofstream file(filename.c_str());
    file << Utils::serialize(signature);
}

void GetSignatureCommand::execute()
{
    std::cout << "GetSignatureCommand::execute() started" << std::endl;
    unsigned int signatureIndex = determineSignatureIndex();
    std::string signatureFilename = determineSignatureFilename();
    send(std::string("get-signature"));
    receive<std::string>(); // OK status
    send(boost::lexical_cast<std::string>(signatureIndex));
    Signature signature = receive<Signature>();
    saveSignature(signatureFilename, signature);
    std::cout << "GetSignatureCommand::execute() finished" << std::endl;
}
