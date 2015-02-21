/**
 * @file RegisterCommand.hpp
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

#ifndef REGISTERCOMMAND_HPP
#define	REGISTERCOMMAND_HPP

#include "../step_out_group_signatures/StepOutGroupSignaturesManager.hpp"
#include "ICommand.hpp"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

class RegisterCommand : public ICommand
{
public:
    /**
     * Constructor of the RegisterCommand class.
     *
     * @param socketInit socket Socket on which the client is connected.
     */
    RegisterCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

    /**
     * Implements the behavior of the "register" command.
     */
    void execute();
private:
    StepOutGroupSignaturesManager& stepOutGroupSignaturesManager; /**< Manager of step-out group signatures. */
};

#endif // REGISTERCOMMAND_HPP
