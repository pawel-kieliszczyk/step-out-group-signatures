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
 *
 * The file contains CheckCommand class which is responsible
 * for interaction between a user and the system during
 * the proof and the step-out procedures.
 */

#ifndef CHECKCOMMAND_HPP
#define	CHECKCOMMAND_HPP

#include "../step_out_group_signatures/PublishedValues.hpp"
#include "../step_out_group_signatures/Signature.hpp"
#include "../step_out_group_signatures/StepOutGroupSignaturesClientManager.hpp"
#include "../step_out_group_signatures/UserPublicKey.hpp"
#include "ICommand.hpp"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include <stdexcept>
#include <string>

/**
 * CheckCommand class.
 *
 * Implements ICommand interface. It is responsible
 * for interaction between a user and the system during
 * the proof and the step-out procedures.
 */
class CheckCommand : public ICommand
{
public:
    /**
     * Constructor of the CheckCommand class.
     *
     * Creates an instance of the class.
     * @param socket Socket used to comunicate with the Group Privacy Server.
     */
    CheckCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

    /**
     * Supports a user during the proof and the step-out procedure.
     */
    void execute();
private:
    /**
     * Checks whether a group member is an author
     * of a step-out group signature.
     *
     * @param userPublicKey
     */
    void checkUser(const unsigned int userIndex,
                   const UserPublicKey& userPublicKey,
                   const PublishedValues& publishedValues,
                   const Signature& signature);

    /**
     * Gets from standart input a name of a file which contains
     * step-out group signature, deserializes the file's content
     * and return the signature.
     *
     * @return Step-out group signature.
     *
     * @throws std::runtime_error Thrown when the provided file doesn't exist.
     */
    Signature determineSignature() throw(std::runtime_error);

    /**
     * Gets from standard input an index number and returns it.
     *
     * @return Provided user's index number.
     */
    unsigned int determineUserIndex();

    /**
     * Checks whether a file of a given name exists.
     *
     * @param filename Name of a file.
     * @return True if the file exists. False otherwise.
     */
    bool fileExists(const std::string& filename);

    /**
     * Extracts content of a given file.
     *
     * @param filename Name of a file.
     * @return Content of the file.
     */
    std::string getFileContent(const std::string& filename);

    StepOutGroupSignaturesClientManager& stepOutGroupSignaturesClientManager; /**< Manager which implements scheme algorithms. */
};

#endif // CHECKCOMMAND_HPP
