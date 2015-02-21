/**
 * @file GroupPrivacyServer.cpp
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
 * This is the main file of Group Privacy Server
 * which includes main() funcion.
 */

#include "group_privacy/manager/GroupPrivacyServerManager.hpp"

#include <boost/asio.hpp>

#include <cstdlib>
#include <iostream>

/**
 * The main() function of Group Privacy Server.
 *
 * Sets a port number and initializes a manager
 * which handles all connections.
 *
 * @param argc Number of arguments.
 * @param argv An array of arguments.
 * @return Error identifier (always zero).
 */
int main(int argc, char* argv[])
{
    const int DEFAULT_PORT = 31337;
    int port = (argc == 1 ? DEFAULT_PORT : std::atoi(argv[1]));
    std::cout << "Starting server on port " << port << "." << std::endl;
    try
    {
        boost::asio::io_service service;
        GroupPrivacyServerManager l_manager(service, port);
        service.run();
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
