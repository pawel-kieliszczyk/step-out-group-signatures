/**
 * @file FinalizeSignatureCommand.cpp
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

#include "FinalizeSignatureCommand.hpp"

#include "../step_out_group_signatures/FinalizeSignatureInput.hpp"
#include "../step_out_group_signatures/FinalizeSignatureOutput.hpp"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <string>

FinalizeSignatureCommand::FinalizeSignatureCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesClientManager(StepOutGroupSignaturesClientManager::instance())
{
}

unsigned int FinalizeSignatureCommand::determineSignatureIndex()
{
    unsigned int signatureIndex;
    std::cin >> signatureIndex;
    return signatureIndex;
}

void FinalizeSignatureCommand::execute()
{
    std::cout << "FinalizeSignatureCommand::execute() started" << std::endl;
    unsigned int signatureIndex = determineSignatureIndex();
    send(std::string("finalize-signature"));
    receive<std::string>(); // OK status
    send(boost::lexical_cast<std::string>(signatureIndex));
    FinalizeSignatureInput input = receive<FinalizeSignatureInput>();
    send(stepOutGroupSignaturesClientManager.createFinalizeProcedureOutput(input));
    std::cout << "FinalizeSignatureCommand::execute() finished" << std::endl;
}
