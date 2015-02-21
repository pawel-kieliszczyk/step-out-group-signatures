/**
 * @file CloseSignatureCommand.hpp
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
 * The file contains CloseSignatureCommand class which is responsible
 * for interaction between a user and the system during closing
 * procedure which desables new users to join signatures.
 */

#ifndef CLOSESIGNATURECOMMAND_HPP
#define	CLOSESIGNATURECOMMAND_HPP

#include "../step_out_group_signatures/StepOutGroupSignaturesClientManager.hpp"
#include "ICommand.hpp"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

/**
 * CloseSignatureCommand class.
 *
 * Implements ICommand interface. It is responsible
 * for interaction between a user and the system during
 * closign procedure which disables new users to join signatures.
 */
class CloseSignatureCommand : public ICommand
{
public:
    /**
     * Constructor of the CloseSignatureCommand class.
     *
     * Creates an instance of the class.
     *
     * @param socket Socket used to comunicate with the Group Privacy Server.
     */
    CloseSignatureCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

    /**
     * Supports a user during the closing procedure.
     */
    void execute();
private:
    /**
     * Gets from standard input a signature's number and returns it.
     *
     * @return Signature's ID.
     */
    unsigned int determineSignatureIndex();

    StepOutGroupSignaturesClientManager& stepOutGroupSignaturesClientManager; /**< Manager which implements scheme algorithms. */
};

#endif // CLOSESIGNATURECOMMAND_HPP
