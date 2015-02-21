/**
 * @file StepOutGroupSignaturesManager.hpp
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
 * The file contains StepOutGroupSignaturesManager class
 * which is responsible for step-out group signatures
 * managing. It implements all methods needed by scheme
 * procedures such as signing, publishing, checking
 * or validating a signature.
 */

#ifndef STEPOUTGROUPSIGNATURESMANAGER_HPP
#define	STEPOUTGROUPSIGNATURESMANAGER_HPP

#include "../key/IKeyPair.hpp"
#include "../key/RSAKey.hpp"
#include "../mpi/BigInteger.hpp"
#include "../polynomial/Polynomial.hpp"
#include "C.hpp"
#include "CheckProcedureInput.hpp"
#include "CloseSignatureInput.hpp"
#include "Delta.hpp"
#include "FinalizeSignatureInput.hpp"
#include "FinalizeSignatureOutput.hpp"
#include "GroupZpValues.hpp"
#include "InitializeSignatureInput.hpp"
#include "JoinSignatureInput.hpp"
#include "PendingSignaturesManager.hpp"
#include "PublishedValues.hpp"
#include "PublishProcedureInput.hpp"
#include "PQPolynomials.hpp"
#include "Sigma.hpp"
#include "Signature.hpp"
#include "SignProcedureInput.hpp"
#include "SignProcedureOutput.hpp"
#include "StepOutGroupSignaturesConstants.hpp"
#include "UserPrivateKey.hpp"
#include "UserPublicKey.hpp"

#include <boost/array.hpp>
#include <boost/noncopyable.hpp>

#include <cstddef>
#include <map>
#include <set>
#include <string>
#include <vector>

/**
 * StepOutGroupSignaturesManager class.
 *
 * The class is responsible for step-out group signatures
 * managiement. It implements all methods needed by scheme
 * procedures such as signing, publishing, checking
 * or validating a signature.
 */
class StepOutGroupSignaturesManager : private boost::noncopyable
{
public:
    /**
     * Calculates polynomials P(t) and Q(t)
     * based on a given x(t) polynomial.
     *
     * @param x Polynomial x(t).
     *
     * @return Polynomials P(t) and Q(t).
     */
    PQPolynomials calculatePQPolynomials(const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x);

    /**
     * Cretes \c FinalizeSignatureInput object containing data
     * needed to perform FinalizeSignature procedure.
     *
     * @param signatureIndex Index number of a signature.
     *
     * @return Object containing data needed to peform FinalizeSignature procedure
     */
    FinalizeSignatureInput createFinalizeSignatureInput(const unsigned int signatureIndex);

    /**
     * Closes a signature of a particular index number.
     *
     * @param input \c CloseSignatureInput object received from Group Privacy Client.
     */
    void closeSignature(const CloseSignatureInput& input);

    /**
     * Performs FinalizeSignature procedure.
     *
     * @param signatureIndex Index number of a signature to be finalized.
     *
     * @param output \c FinalizeSignatureOutput object received from Group Privacy Client.
     */
    void finalizeSignature(const unsigned int signatureIndex, const FinalizeSignatureOutput& output);

    /**
     * Returns the dummy user's private key.
     *
     * @return Dummy user's private key.
     */
    const UserPrivateKey& getDummyUserPrivateKey();

    /**
     * Return group specific values (p, q and g).
     *
     * @return Group specific values.
     */
    const GroupZpValues& getGroupZpValues() const;

    /**
     * Returns published user's data needed to perform
     * Check procedure.
     *
     * @param inputObject containing user's index number and value t.
     *
     * @return Published user's data.
     */
    const PublishedValues& getPublishedValues(const CheckProcedureInput& input);

    /**
     * Returns Group Privacy Server's public key.
     *
     * @return Group Privacy Server's public key.
     */
    const RSAKey& getServerPublicKey() const;

    /**
     * Returns step-out group signature of a given index number.
     *
     * @param signatureIndex Index number of the signature.
     *
     * @return Step-out group signature.
     */
    Signature getSignature(const unsigned int signatureIndex);

    /**
     * Returns \c t value from signature of a given index number.
     *
     * @param signatureIndex Index number of the signature.
     *
     * @return Value from the signature.
     */
    BigInteger getTFromPendingSignature(const unsigned int signatureIndex);

    /**
     * Returns user's public key.
     *
     * @param userIndex Index number of the user.
     *
     * @return User's public key.
     */
    const UserPublicKey& getUserPublicKey(const unsigned int userIndex) const;

    /**
     * Checks whether a user has published data
     * needed to perform Check procedure.
     *
     * @param input Object containing user's index number and value t.
     *
     * @return True if the user has published the data. False otherwise.
     */
    bool hasPublishedValues(const CheckProcedureInput& input);

    /**
     * Creates a new pending signature with open status.
     *
     * @param input Object containing user's index, message to sign and value x.
     *
     * @return Unique signature's number.
     */
    unsigned int initializeSignature(const InitializeSignatureInput& input);

    /**
     * Return the only instance of the \c StepOutGroupSignaturesManager class.
     *
     * @return Instance of the \c StepOutGroupSignaturesManager class.
     */
    static StepOutGroupSignaturesManager& instance();

    /**
     * Adds a user to a set of signature's creators.
     *
     * @param input Object containing user's index and value x(t).
     */
    void joinSignature(const unsigned int signatureIndex, const JoinSignatureInput& input);

    /**
     * Published user's data needed to perform Check procedure.
     *
     * @param input Object containing user's data.
     */
    void publish(const PublishProcedureInput& input);

    /**
     * Registers a new user in the group.
     *
     * @param p_userPublicKey User's publis key.
     *
     * @return Index number assigned to the user.
     */
    std::size_t registerNewUser(const UserPublicKey& p_userPublicKey);

    /**
     * Performs the server's part of the Sign procedure.
     *
     * @param input Object containing data obtained from Group Privacy Client.
     *
     * @return Calculated necessary data to finish the Sign procedure.
     */
    SignProcedureOutput sign(const SignProcedureInput& input);
private:
    StepOutGroupSignaturesManager();
    BigInteger calculateL(const BigInteger& t, const BigInteger& x);
    Polynomial<SGS::P_POLYNOMIAL_DEGREE> calculatePPolynomial(const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x);
    Polynomial<SGS::Q_POLYNOMIAL_DEGREE> calculateQPolynomial(const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x);
    BigInteger calculateT(const BigInteger& x, const std::string& message);
    const std::size_t countSigners(const unsigned int signatureIndex);
    C createC(const BigInteger& t, const BigInteger& x, const BigInteger& r);
    Delta createDelta(const BigInteger& t, const std::size_t d, const BigInteger& r);
    void createDummyUserPrivateKey();
    void createDummyUserXPolynomial();
    std::string createH(const std::string& message, const std::string& Z);
    Sigma createSigma(const C& c, const Delta& delta, const std::string& h);
    std::string createZ(const unsigned int signatureIndex);
    Polynomial<SGS::L_EXP_POLYNOMIAL_DEGREE> expandLPolynomial(const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x);
    void initializeGroup();
    void initializeGroupZpValues();
    void initializeKeyPair();
    void initializePQ();
    void initializeG();
    void initializeAPolynomials();
    void initializeSPolynomial();
    template<std::size_t D>
    void randomizePolynomial(Polynomial<D>& p_poly);
    SignProcedureOutput sign(const BigInteger& t, const BigInteger& x, const std::size_t d, const std::string& h);

    static StepOutGroupSignaturesManager                 sgs;

    GroupZpValues                                        groupZpValues;
    boost::shared_ptr<IKeyPair>                          keyPair;
    boost::shared_ptr<UserPrivateKey>                    dummyUserPrivateKey;
    boost::array<Polynomial<SGS::A_POLYNOMIAL_DEGREE>,
                 SGS::NUMBER_OF_A_POLYNOMIALS>           aPolys;
    Polynomial<SGS::S_POLYNOMIAL_DEGREE>                 sPoly;
    std::vector<UserPublicKey>                           usersPublicKeys;
    std::map<unsigned int, std::set<PublishedValues> >   publishedUsersSecrets;
    PendingSignaturesManager                             pendingSignaturesManager;
};

#endif // STEPOUTGROUPSIGNATURESMANAGER_HPP
