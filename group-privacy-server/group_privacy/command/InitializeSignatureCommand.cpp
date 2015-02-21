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

#include <iostream>

InitializeSignatureCommand::InitializeSignatureCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesManager(StepOutGroupSignaturesManager::instance())
{
}

void InitializeSignatureCommand::execute()
{
    std::cout << "InitializeSignatureCommand::execute() started" << std::endl;
    send(std::string("ok"));
    InitializeSignatureInput input = receive<InitializeSignatureInput>();
    unsigned int signatureIndex = stepOutGroupSignaturesManager.initializeSignature(input);
    send(boost::lexical_cast<std::string>(signatureIndex));
    std::cout << "InitializeSignatureCommand::execute() finished" << std::endl;
}
