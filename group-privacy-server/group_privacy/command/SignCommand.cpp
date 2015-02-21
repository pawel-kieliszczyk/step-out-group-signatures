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
 */

#include "SignCommand.hpp"

#include "../step_out_group_signatures/SignProcedureInput.hpp"
#include "../step_out_group_signatures/SignProcedureOutput.hpp"
#include "SerializationUtils.hpp"

SignCommand::SignCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesManager(StepOutGroupSignaturesManager::instance())
{
}

void SignCommand::execute()
{
    std::cout << "SignCommand::execute() started" << std::endl;
    send(std::string("ok"));
    SignProcedureInput input = receive<SignProcedureInput>();
    send(stepOutGroupSignaturesManager.sign(input));
    std::cout << "SignCommand::execute() finished" << std::endl;

//    std::cout << "SignCommand::execute() started" << std::endl;
//    socketManager.send("ok");
//    std::string serializedInput = socketManager.receive();
//    SignProcedureInput input = Utils::deserialize<SignProcedureInput>(serializedInput);
//    SignProcedureOutput output = stepOutGroupSignaturesManager.sign(input);
//    std::string serializedOutput = Utils::serialize(output);
//    socketManager.send(serializedOutput);
//    std::cout << "SignCommand::execute() finished" << std::endl;
}
