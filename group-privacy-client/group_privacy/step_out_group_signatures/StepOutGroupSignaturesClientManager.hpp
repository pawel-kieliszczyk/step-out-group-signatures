/**
 * @file StepOutGroupSignaturesClientManager.hpp
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
 * The file contains StepOutGroupSignaturesClientManager class
 * which is responsible for step-out group signatures
 * managing. It implements all methods needed by scheme
 * procedures such as signing, publishing, checking
 * or validating a signature.
 */

#ifndef STEPOUTGROUPSIGNATURESCLIENTMANAGER_HPP
#define	STEPOUTGROUPSIGNATURESCLIENTMANAGER_HPP

#include "../key/IKey.hpp"
#include "../mpi/BigInteger.hpp"
#include "../polynomial/Polynomial.hpp"
#include "../polynomial_in_the_exponent/PolynomialInTheExponent.hpp"
#include "CheckProcedureInput.hpp"
#include "CloseSignatureInput.hpp"
#include "FinalizeSignatureInput.hpp"
#include "FinalizeSignatureOutput.hpp"
#include "GroupZpValues.hpp"
#include "InitializeSignatureInput.hpp"
#include "JoinSignatureInput.hpp"
#include "PQPolynomials.hpp"
#include "Psi.hpp"
#include "PublishedValues.hpp"
#include "PublishProcedureInput.hpp"
#include "Signature.hpp"
#include "SignProcedureInput.hpp"
#include "SignProcedureOutput.hpp"
#include "StepOutGroupSignaturesConstants.hpp"
#include "Theta.hpp"
#include "ThetaPrim.hpp"
#include "UserPrivateKey.hpp"
#include "UserPublicKey.hpp"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <cstddef>
#include <set>
#include <string>

/**
 * StepOutGroupSignaturesClientManager class.
 *
 * The class is responsible for step-out group signatures
 * managing. It implements all methods needed by scheme
 * procedures such as signing, publishing, checking
 * or validating a signature.
 */
class StepOutGroupSignaturesClientManager : private boost::noncopyable
{
public:
    /**
     * Creates \c CheckProcedureInput object which includes data
     * needed to perform Check procedure.
     *
     * @param index Index number of a user that is to be checked.
     * @param signature Step-out group signature.
     *
     * @return Object contaning data needed to perform Check procedure.
     */
    CheckProcedureInput createCheckProcedureInput(const unsigned int index, const Signature& signature);

    /**
     * Creates \c CloseSignatureInput object which includes data
     * needed to perform CloseSignature procedure.
     *
     * @param signatureIndex Index number of a signature.
     *
     * @return Object contaning data needed to perform CloseSignature procedure.
     */
    CloseSignatureInput createCloseSignatureInput(const unsigned int signatureIndex);

    /**
     * Process a given \c FinalizeSignatureInput object received from
     * Group Privacy Server and creates \c FinalizeSignatureOutput object.
     *
     * @param input Data sent from the server durin FinalizeSignature procedure.
     *
     * @return Object contaning data needed to finish FinalizeSignature procedure.
     */
    FinalizeSignatureOutput createFinalizeProcedureOutput(const FinalizeSignatureInput& input);

    /**
     * Creates \c InitializeSignatureInput object which includes data
     * needed to perform InitializeSignature procedure.
     *
     * @param message Message to sign.
     *
     * @return Object containing data needed to perform InitializeSignature procedure.
     */
    InitializeSignatureInput createInitializeSignatureInput(const std::string& message);

    /**
     * Creates \c JoinSignatureInput object which includes data
     * needed to perform JoinSignature procedure.
     *
     * @param t Values received from Group Privacy Server during JoinSignature procedure.
     *
     * @return Object containing data needed to perform JoinSignature procedure.
     */
    JoinSignatureInput createJoinSignatureInput(const BigInteger& t);

    /**
     * Creates user's private and public key.
     *
     * @param polynomials Object containing polynomials P(t) and Q(t)
     *
     * @return Created user's public key.
     */
    const UserPublicKey& createKeys(const PQPolynomials& polynomials);

    /**
     * Creates \c PublishProcedureInput object which includes data
     * needed to perform Publish procedure.
     *
     * @param signature Step-out group signature.
     *
     * @return Object contaning data needed to perform Publish procedure.
     */
    PublishProcedureInput createPublishProcedureInput(const Signature& signature) const;

    /**
     * Creates step-out group signature.
     *
     * @param input Data sent to the Group Privacy Server during Sign procedure.
     * @param output Data received from the Group Privacy Server during Sign procedure.
     *
     * @return Step-out group signature.
     */
    Signature createSignature(const SignProcedureInput& input, const SignProcedureOutput& output);

    /**
     * Creates \c SignProcedureInputobject which includes data
     * needed to perform Sign procedure.
     *
     * @param messageToSign Message to sign.
     *
     * @return Object contaning data needed to perform Sign procedure.
     */
    const SignProcedureInput createSignProcedureInput(const std::string& messageToSign);

    /**
     * Returns user's index number assigned by Group Privacy Server
     * during registration procedure.
     *
     * @return User's index number if the user is a registered group Member. "?" otherwise.
     */
    std::string getUserIndex() const;

    /**
     * Returns user's secret x(t) polynomial which comes from
     * his/her private key.
     *
     * @return User's secret x(t) polynomial.
     */
    const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& getXPolynomial() const;

    /**
     * Initialies user's private and public key.
     */
    void initializeUserKeys();

    /**
     * Return the only instance of the \c StepOutGroupSignaturesClientManager class.
     *
     * @return Instance of the \c StepOutGroupSignaturesClientManager class.
     */
    static StepOutGroupSignaturesClientManager& instance();

    /**
     * Checks whether a group member has created a given step-out group signature.
     *
     * @param publicKey User's public key to check.
     * @param publishedValues Data published by the user that is to be checked.
     * @param signature Step-out group signature.
     *
     * @return True if the user has not signed the given signature. False otherwise.
     */
    bool isNotSigner(const UserPublicKey& publicKey,
                     const PublishedValues& publishedValues,
                     const Signature& signature) const;

    /**
     * Checks whether a group member has created a given step-out group signature.
     *
     * @param publicKey User's public key to check.
     * @param publishedValues Data published by the user that is to be checked.
     * @param signature Step-out group signature.
     *
     * @return True if the user has signed the given signature. False otherwise.
     */
    bool isSigner(const UserPublicKey& publicKey,
                  const PublishedValues& publishedValues,
                  const Signature& signature) const;

    /**
     * Sets the dummy user's private key.
     *
     * @param dummyUserPrivateKey Dummy user's private key.
     */
    void setDummyUserPrivateKey(const UserPrivateKey& dummyUserPrivateKey);

    /**
     * Sets group specific values (p, q and g).
     *
     * @param groupZpValuesInit group specific values.
     */
    void setGroupZpValues(const GroupZpValues& groupZpValuesInit);

    /**
     * Sets the Group Privacy Server's public key.
     *
     * @param serverPublicKeyInit Group Privacy Server's public key.
     */
    void setServerPublicKey(const IKey& serverPublicKeyInit);

    /**
     * Sets user's index number received from Group Privacy Server
     * during registration procedure.
     *
     * @param userIndexInit User's index number.
     */
    void setUserIndex(const unsigned int userIndexInit);

    /**
     * Verifies whether a given step-out group signature matches
     * the given message.
     *
     * @param message A message.
     * @param signature Step-out group signature.
     *
     * @return True if the given step-out group signature is valid. False otherwise.
     */
    bool verifySignature(const std::string& message, const Signature& signature);
private:
    StepOutGroupSignaturesClientManager();
    std::string createH(const std::string& message, const ThetaPrim& thetaPrim);
    Psi createPsi(const Delta& delta, const Theta& theta, const PsiElement& psiElement) const;
    Theta createTheta(const ThetaPrim& thetaPrim) const;
    ThetaElement createThetaElement(const ThetaPrimElement& thetaPrimElement) const;
    ThetaPrim createThetaPrim(const SignProcedureInput& input, const SignProcedureOutput& output);
    template<std::size_t D>
    void randomizePolynomial(Polynomial<D>& p_poly);
    bool verifyInterpolation(const Signature& signature);
    bool verifyMessageHash(const std::string& message, const Signature& signature);
    bool verifySigma(const std::string& message, const Signature& signature);

    static StepOutGroupSignaturesClientManager   manager;

    boost::shared_ptr<GroupZpValues>             groupZpValues;
    boost::shared_ptr<IKey>                      serverPublicKey;
    boost::shared_ptr<UserPrivateKey>            dummyUserPrivateKey;
    boost::shared_ptr<UserPrivateKey>            userPrivateKey;
    boost::shared_ptr<UserPublicKey>             userPublicKey;
    boost::shared_ptr<unsigned int>              userIndex;
    bool                                         registered;
};

#endif // STEPOUTGROUPSIGNATURESCLIENTMANAGER_HPP
