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
 */

#include "RegisterCommand.hpp"

#include "../step_out_group_signatures/GroupZpValues.hpp"
#include "../step_out_group_signatures/OPEProcedureInput.hpp"
#include "../step_out_group_signatures/OPEProcedureOutput.hpp"
#include "../step_out_group_signatures/UserPublicKey.hpp"
#include "SerializationUtils.hpp"

#include <boost/lexical_cast.hpp>

#include <cstddef>

RegisterCommand::RegisterCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : ICommand(socket),
      stepOutGroupSignaturesManager(StepOutGroupSignaturesManager::instance())
{
}

void RegisterCommand::execute()
{
    std::cout << "RegisterCommand::execute() started" << std::endl;
    send(stepOutGroupSignaturesManager.getGroupZpValues());
    receive<std::string>(); // OK status
    send(stepOutGroupSignaturesManager.getServerPublicKey());
    Polynomial<SGS::X_POLYNOMIAL_DEGREE> x = receive<Polynomial<SGS::X_POLYNOMIAL_DEGREE> >();
    send(stepOutGroupSignaturesManager.calculatePQPolynomials(x));
    UserPublicKey userPublicKey = receive<UserPublicKey>();
    send(boost::lexical_cast<std::string>(stepOutGroupSignaturesManager.registerNewUser(userPublicKey)));
    std::cout << "RegisterCommand::execute() finished" << std::endl;

//    std::cout << "RegisterCommand::execute() started" << std::endl;
//    const GroupZpValues& groupZpValues = stepOutGroupSignaturesManager.getGroupZpValues();
//    std::string serializedGroupZpValues = Utils::serialize(groupZpValues);
//    socketManager.send(serializedGroupZpValues);
//    socketManager.receive(); // OK status
//    const RSAKey& serverPublicKey = stepOutGroupSignaturesManager.getServerPublicKey();
//    std::string serializedServerPublicKey = Utils::serialize(serverPublicKey);
//    socketManager.send(serializedServerPublicKey);
//    //std::string serializedInput = socketManager.receive();
//    //OPEProcedureInput input = Utils::deserialize<OPEProcedureInput>(serializedInput);
//    //OPEProcedureOutput output = stepOutGroupSignaturesManager.performOPE(input);
//    //std::string serializedOutput = Utils::serialize(output);
//    //socketManager.send(serializedOutput);
//    std::string serializedX = socketManager.receive();
//    Polynomial<SGS::X_POLYNOMIAL_DEGREE> x = Utils::deserialize<Polynomial<SGS::X_POLYNOMIAL_DEGREE> >(serializedX);
//    PQPolynomials polynomials = stepOutGroupSignaturesManager.calculatePQPolynomials(x);
//    std::string serializedPolynomials = Utils::serialize(polynomials);
//    socketManager.send(serializedPolynomials);
//    std::string serializedUserPublicKey = socketManager.receive();
//    UserPublicKey userPublicKey = Utils::deserialize<UserPublicKey>(serializedUserPublicKey);
//    std::size_t userIndex = stepOutGroupSignaturesManager.registerNewUser(userPublicKey);
//    std::string serializedUserIndex = boost::lexical_cast<std::string>(userIndex);
//    socketManager.send(serializedUserIndex);
//    std::cout << "User " << userIndex << " registered." << std::endl;
//    std::cout << "RegisterCommand::execute() finished" << std::endl;
}
