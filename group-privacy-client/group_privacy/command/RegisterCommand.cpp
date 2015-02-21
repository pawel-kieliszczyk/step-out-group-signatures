/**
 * @file RegisterCommand.cpp
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
 * \c RegisterCommand class.
 */

#include "RegisterCommand.hpp"

#include "../key/RSAKey.hpp"
#include "../step_out_group_signatures/GroupZpValues.hpp"
#include "../step_out_group_signatures/OPEProcedureInput.hpp"
#include "../step_out_group_signatures/OPEProcedureOutput.hpp"

#include <boost/lexical_cast.hpp>

#include <cstddef>

RegisterCommand::RegisterCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesClientManager(StepOutGroupSignaturesClientManager::instance())
{
}

void RegisterCommand::execute()
{
    std::cout << "RegisterCommand::execute() started" << std::endl;
    send(std::string("register"));
    stepOutGroupSignaturesClientManager.setGroupZpValues(receive<GroupZpValues>());
    send(std::string("ok"));
    stepOutGroupSignaturesClientManager.setServerPublicKey(receive<RSAKey>());
    stepOutGroupSignaturesClientManager.initializeUserKeys();
    send(stepOutGroupSignaturesClientManager.getXPolynomial());
    PQPolynomials polynomials = receive<PQPolynomials>();
    send(stepOutGroupSignaturesClientManager.createKeys(polynomials));
    stepOutGroupSignaturesClientManager.setUserIndex(boost::lexical_cast<unsigned int>(receive<std::string>()));
    std::cout << "RegisterCommand::execute() finished" << std::endl;

//    std::cout << "RegisterCommand::execute() started" << std::endl;
//    socketManager.send("register");
//    std::string serializedGroupZpValues = socketManager.receive();
//    GroupZpValues groupZpValues = Utils::deserialize<GroupZpValues>(serializedGroupZpValues);
//    stepOutGroupSignaturesClientManager.setGroupZpValues(groupZpValues);
//    socketManager.send("ok");
//    std::string serializedServerPublicKey = socketManager.receive();
//    RSAKey serverPublicKey = Utils::deserialize<RSAKey>(serializedServerPublicKey);
//    stepOutGroupSignaturesClientManager.setServerPublicKey(serverPublicKey);
//    //OPEProcedureInput input = stepOutGroupSignaturesClientManager.generateOPEProcedureInput();
//    //std::string serializedOPEProcedureInput = Utils::serialize(input);
//    //socketManager.send(serializedOPEProcedureInput);
//    //std::string serializedOutput = socketManager.receive();
//    //OPEProcedureOutput output = Utils::deserialize<OPEProcedureOutput>(serializedOutput);
//    //const UserPublicKey& userPublicKey = stepOutGroupSignaturesClientManager.createKeys(input, output);
//    stepOutGroupSignaturesClientManager.initializeUserKeys();
//    const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x = stepOutGroupSignaturesClientManager.getXPolynomial();
//    std::string serializedX = Utils::serialize(x);
//    socketManager.send(serializedX);
//    std::string serializedPolynomials = socketManager.receive();
//    PQPolynomials polynomials = Utils::deserialize<PQPolynomials>(serializedPolynomials);
//    const UserPublicKey& userPublicKey = stepOutGroupSignaturesClientManager.createKeys(polynomials);
//    std::string serializedUserPublicKey = Utils::serialize(userPublicKey);
//    socketManager.send(serializedUserPublicKey);
//    std::string serializedUserIndex = socketManager.receive();
//    std::size_t userIndex = boost::lexical_cast<std::size_t>(serializedUserIndex);
//    stepOutGroupSignaturesClientManager.setUserIndex(userIndex);
//    std::cout << "RegisterCommand::execute() finished" << std::endl;
}
