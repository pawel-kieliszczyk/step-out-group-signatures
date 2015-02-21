/**
 * @file SignCommand.hpp
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
 * creation of a signature.
 */

#ifndef SIGNCOMMAND_HPP
#define	SIGNCOMMAND_HPP

#include "../step_out_group_signatures/Signature.hpp"
#include "../step_out_group_signatures/StepOutGroupSignaturesClientManager.hpp"
#include "ICommand.hpp"

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include <stdexcept>
#include <string>

/**
 * SignCommand class.
 *
 * Implements ICommand interface. It is responsible
 * for interaction between a user and the system during
 * creation of a signature.
 */
class SignCommand : public ICommand
{
public:
    /**
     * Constructor of the SignCommand class.
     *
     * Creates an instance of the class.
     *
     * @param socket Socket used to comunicate with the Group Privacy Server.
     */
    SignCommand(boost::shared_ptr<boost::asio::ip::tcp::socket> socket);

    /**
     * Supports a user during creation of a signature.
     */
    void execute();
private:
    /**
     * Gets from standart input a name of a file which contains
     * a message to sign and return this name and the file's
     * content.
     *
     * @return Tuple containing message's filename and content.
     *
     * @throws std::runtime_error Thrown when the provided file doesn't exist.
     */
    boost::tuple<std::string, std::string> determineMessage() throw(std::runtime_error);

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

    /**
     * Takes a name of a file from standard input.
     *
     * @return Name of the file.
     */
    std::string getFilename();

    /**
     * Creates a file containing a given signature on the disk.
     *
     * @param filename Name of the file.
     * @param signature The step-out group signature.
     */
    void saveSignature(const std::string& filename, const Signature& signature);

    StepOutGroupSignaturesClientManager& stepOutGroupSignaturesClientManager; /**< Manager which implements scheme algorithms. */
};

#endif // SIGNCOMMAND_HPP
