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
 */

#include "VerifyCommand.hpp"

#include "../step_out_group_signatures/PublishProcedureInput.hpp"
#include "SerializationUtils.hpp"

VerifyCommand::VerifyCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesManager(StepOutGroupSignaturesManager::instance())
{
}

void VerifyCommand::execute()
{
    std::cout << "VerifyCommand::execute() started" << std::endl;
    send(stepOutGroupSignaturesManager.getGroupZpValues());
    receive<std::string>();
    send(stepOutGroupSignaturesManager.getServerPublicKey());
    receive<std::string>();
    send(stepOutGroupSignaturesManager.getDummyUserPrivateKey());
    std::cout << "VerifyCommand::execute() finished" << std::endl;

//    std::cout << "VerifyCommand::execute() started" << std::endl;
//    const GroupZpValues& groupZpValues = stepOutGroupSignaturesManager.getGroupZpValues();
//    std::string serializedGroupZpValues = Utils::serialize(groupZpValues);
//    socketManager.send(serializedGroupZpValues);
//    socketManager.receive(); // OK status
//    const RSAKey& serverPublicKey = stepOutGroupSignaturesManager.getServerPublicKey();
//    std::string serializedServerPublicKey = Utils::serialize(serverPublicKey);
//    socketManager.send(serializedServerPublicKey);
//    socketManager.receive(); // OK status
//    const UserPrivateKey& dummyUserPrivateKey = stepOutGroupSignaturesManager.getDummyUserPrivateKey();
//    std::string serializedDummyUserPrivateKey = Utils::serialize(dummyUserPrivateKey);
//    socketManager.send(serializedDummyUserPrivateKey);
//    std::cout << "VerifyCommand::execute() finished" << std::endl;
}
