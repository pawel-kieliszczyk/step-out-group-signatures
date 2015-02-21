/**
 * @file CheckCommand.hpp
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

#include "CheckCommand.hpp"

#include "../step_out_group_signatures/CheckProcedureInput.hpp"
#include "../step_out_group_signatures/PublishProcedureInput.hpp"
#include "SerializationUtils.hpp"

CheckCommand::CheckCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesManager(StepOutGroupSignaturesManager::instance())
{
}

void CheckCommand::execute()
{
    std::cout << "CheckCommand::execute() started" << std::endl;
    send("ok");
    CheckProcedureInput checkProcedureInput = receive<CheckProcedureInput>();
    if(stepOutGroupSignaturesManager.hasPublishedValues(checkProcedureInput))
    {
        send(std::string("yes"));
        receive<std::string>();
        send(stepOutGroupSignaturesManager.getUserPublicKey(checkProcedureInput.getUserIndex()));
        receive<std::string>();
        send(stepOutGroupSignaturesManager.getPublishedValues(checkProcedureInput));
    }
    else
        send(std::string("no"));
    std::cout << "CheckCommand::execute() finished" << std::endl;

//    std::cout << "CheckCommand::execute() started" << std::endl;
//    socketManager.send("ok");
//    std::string serializedCheckProcedureInput = socketManager.receive();
//    CheckProcedureInput checkProcedureInput = Utils::deserialize<CheckProcedureInput>(serializedCheckProcedureInput);
//    if(stepOutGroupSignaturesManager.hasPublishedValues(checkProcedureInput))
//    {
//        socketManager.send("yes");
//        socketManager.receive(); // OK status
//        const UserPublicKey& userPublicKey =
//            stepOutGroupSignaturesManager.getUserPublicKey(checkProcedureInput.getUserIndex());
//        std::string serializedUserPublicKey = Utils::serialize(userPublicKey);
//        socketManager.send(serializedUserPublicKey);
//        socketManager.receive(); // OK status
//        const PublishedValues& publishedValues = stepOutGroupSignaturesManager.getPublishedValues(checkProcedureInput);
//        std::string serializedPublishedValues = Utils::serialize(publishedValues);
//        socketManager.send(serializedPublishedValues);
//    }
//    else
//        socketManager.send("no");
//    std::cout << "CheckCommand::execute() finished" << std::endl;
}
