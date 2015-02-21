/**
 * @file GroupPrivacyClient.cpp
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
 * This is the main file of Group Privacy Client
 * which includes main() funcion.
 */

#include "group_privacy/manager/GroupPrivacyClientManager.hpp"

#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    const std::string DEFAULT_HOST = "127.0.0.1";
    const std::string DEFAULT_PORT = "31337";
    std::string host = (argc > 1 ? std::string(argv[1]) : DEFAULT_HOST);
    std::string port = (argc > 2 ? std::string(argv[2]) : DEFAULT_PORT);
    try
    {
        GroupPrivacyClientManager groupPrivacyClientManager(host, port);
        groupPrivacyClientManager.manage();
    }
    catch(std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
