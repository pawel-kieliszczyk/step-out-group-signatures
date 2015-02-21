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
 */

#include "StepOutGroupSignaturesManager.hpp"

#include "../digital_signature/DigitalSignatureManager.hpp"
#include "../hash/HMAC_SHA256.hpp"
#include "../hash/SHA256.hpp"
#include "../key/RSAKeyPair.hpp"
#include "Utils.hpp"
#include "CheckProcedureInput.hpp"
#include "InitializeSignatureInput.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/assign.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <algorithm>
#include <iterator>
#include <map>
#include <sstream>
#include <utility>

StepOutGroupSignaturesManager StepOutGroupSignaturesManager::sgs;

StepOutGroupSignaturesManager::StepOutGroupSignaturesManager()
{
    initializeGroupZpValues();
    initializeKeyPair();
    initializeGroup();
    createDummyUserPrivateKey();
}

BigInteger StepOutGroupSignaturesManager::calculateL(const BigInteger& t, const BigInteger& x)
{
    Polynomial<SGS::L_POLYNOMIAL_DEGREE> lPolynomial;
    for(std::size_t i = 0; i < SGS::L_POLYNOMIAL_DEGREE; ++i)
    {
        lPolynomial[i] = aPolys[i](t, groupZpValues.q);
    }
    return lPolynomial(x, groupZpValues.q);
}

Polynomial<SGS::P_POLYNOMIAL_DEGREE> StepOutGroupSignaturesManager::calculatePPolynomial(
    const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x)
{
    Polynomial<SGS::L_EXP_POLYNOMIAL_DEGREE> expandedLPolynomial = expandLPolynomial(x);
    return mod<SGS::L_EXP_POLYNOMIAL_DEGREE, SGS::S_POLYNOMIAL_DEGREE, SGS::P_POLYNOMIAL_DEGREE>(expandedLPolynomial,
                                                                                                 sPoly,
                                                                                                 groupZpValues.q);
}

PQPolynomials StepOutGroupSignaturesManager::calculatePQPolynomials(const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x)
{
    Polynomial<SGS::P_POLYNOMIAL_DEGREE> p = calculatePPolynomial(x);
    Polynomial<SGS::Q_POLYNOMIAL_DEGREE> q = calculateQPolynomial(x);
    PolynomialInTheExponent<SGS::Q_POLYNOMIAL_DEGREE> gQ;
    for(std::size_t i = 0; i <= SGS::Q_POLYNOMIAL_DEGREE; ++i)
    {
        gQ[i] = powm(groupZpValues.g, q[i], groupZpValues.p);
    }
    return PQPolynomials(p, gQ);
}

Polynomial<SGS::Q_POLYNOMIAL_DEGREE> StepOutGroupSignaturesManager::calculateQPolynomial(
    const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x)
{
    Polynomial<SGS::L_EXP_POLYNOMIAL_DEGREE> expandedLPolynomial = expandLPolynomial(x);
    return divide<SGS::L_EXP_POLYNOMIAL_DEGREE,
                  SGS::S_POLYNOMIAL_DEGREE,
                  SGS::Q_POLYNOMIAL_DEGREE>(expandedLPolynomial, sPoly, groupZpValues.q);
}

BigInteger StepOutGroupSignaturesManager::calculateT(const BigInteger& x, const std::string& message)
{
    HMAC_SHA256 keyedHasher;
    keyedHasher.setKey(x.toString());
    keyedHasher.setText(message);
    BigInteger t(keyedHasher.getHexHash());
    return (t % groupZpValues.q);
}

void StepOutGroupSignaturesManager::closeSignature(const CloseSignatureInput& input)
{
    bool closed = pendingSignaturesManager.closePendingSignature(input.getSignatureIndex(), input.getUserIndex());
    if(closed)
    {
        const BigInteger& t = pendingSignaturesManager.getPendingSignature(input.getSignatureIndex()).getT();
        const std::size_t d = countSigners(input.getSignatureIndex());
        // generate r from Zq at random
        BigInteger::RandomGenerator randomGenerator(SGS::COEFFICIENTS_NBITS);
        BigInteger r = randomGenerator() % groupZpValues.q;
        Delta delta = createDelta(t, d, r);
        const BigInteger& x = pendingSignaturesManager.getPendingSignature(input.getSignatureIndex()).getX();
        C c = createC(t, x , r);
        std::string Z = createZ(input.getSignatureIndex());
        std::string h = createH(pendingSignaturesManager.getPendingSignature(input.getSignatureIndex()).getMessage(), Z);
        Sigma sigma = createSigma(c, delta, h);
        pendingSignaturesManager.getPendingSignature(input.getSignatureIndex()).setDelta(delta);
        pendingSignaturesManager.getPendingSignature(input.getSignatureIndex()).setC(c);
        pendingSignaturesManager.getPendingSignature(input.getSignatureIndex()).setSigma(sigma);
    }
}

const std::size_t StepOutGroupSignaturesManager::countSigners(const unsigned int signatureIndex)
{
    return pendingSignaturesManager.getPendingSignature(signatureIndex).getSignersXtValues().size();
}

C StepOutGroupSignaturesManager::createC(const BigInteger& t, const BigInteger& x, const BigInteger& r)
{
    return C(powm(groupZpValues.g, r, groupZpValues.p),
             (r * sPoly(t, groupZpValues.q)) % groupZpValues.q,
             powm(groupZpValues.g, r * calculateL(t, x), groupZpValues.p));
}

Delta StepOutGroupSignaturesManager::createDelta(const BigInteger& t, const std::size_t d, const BigInteger& r)
{
    const std::size_t DELTA_SIZE = SGS::MAXIMAL_NUMBER_OF_SIGNERS - d;
    Delta delta;
    for(std::size_t i = 1; i <= DELTA_SIZE; ++i)
    {
        DeltaElement deltaElement(BigInteger(i), powm(groupZpValues.g,
                                                      (r * calculateL(t, BigInteger(i))) % groupZpValues.q,
                                                      groupZpValues.p));
        delta.push_back(deltaElement);
    }
    return delta;
}

void StepOutGroupSignaturesManager::createDummyUserPrivateKey()
{
    dummyUserPrivateKey.reset(new UserPrivateKey());
    randomizePolynomial(dummyUserPrivateKey->getX());
    createDummyUserXPolynomial();
    dummyUserPrivateKey->setP(calculatePPolynomial(dummyUserPrivateKey->getX()));
    Polynomial<SGS::Q_POLYNOMIAL_DEGREE> qPoly(calculateQPolynomial(dummyUserPrivateKey->getX()));
    for(std::size_t i = 0; i <= SGS::Q_POLYNOMIAL_DEGREE; ++i)
    {
        dummyUserPrivateKey->getQ()[i] = powm(groupZpValues.g, qPoly[i], groupZpValues.p);
    }
}

void StepOutGroupSignaturesManager::createDummyUserXPolynomial()
{
    randomizePolynomial(dummyUserPrivateKey->getX());
}

FinalizeSignatureInput StepOutGroupSignaturesManager::createFinalizeSignatureInput(const unsigned int signatureIndex)
{
    const PendingSignature& pendingSignature = pendingSignaturesManager.getPendingSignature(signatureIndex);
    return FinalizeSignatureInput(pendingSignature.getT(),
                                  pendingSignature.getC().gr(),
                                  pendingSignature.getC().rSt());
}

std::string StepOutGroupSignaturesManager::createH(const std::string& message, const std::string& Z)
{
    SHA256 hasher;
    hasher.setText(message + Z);
    return hasher.getHexHash();
}

Sigma StepOutGroupSignaturesManager::createSigma(const C& c, const Delta& delta, const std::string& h)
{
    std::string strC = Utils::createString(c);
    std::string strDelta = Utils::createString(delta);
    SHA256 hasher;
    hasher.setText(strC + strDelta + h);
    Sigma sigma = DigitalSignatureManager::sign(hasher.getHash(),
                                                hasher.getHashLength(),
                                                keyPair->getPrivateKey());
    return sigma;
}

std::string StepOutGroupSignaturesManager::createZ(const unsigned int signatureIndex)
{
    using namespace boost::assign;
    const PendingSignature& pendingSignature = pendingSignaturesManager.getPendingSignature(signatureIndex);
    const std::map<unsigned int, BigInteger>& signersXtValues = pendingSignature.getSignersXtValues();
    std::vector<BigInteger> xtValues;
    for(std::map<unsigned int, BigInteger>::const_iterator it = signersXtValues.begin();
        it != signersXtValues.end();
        ++it)
    {
        xtValues += it->second;
    }
    std::sort(xtValues.begin(), xtValues.end());
    std::string Z = "";
    BOOST_FOREACH(const BigInteger& xt, xtValues)
        Z += xt.toString();
    return Z;
}

Polynomial<SGS::L_EXP_POLYNOMIAL_DEGREE> StepOutGroupSignaturesManager::expandLPolynomial(
    const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& x)
{
    Polynomial<SGS::L_EXP_POLYNOMIAL_DEGREE> expandedLPolynomial;
    for(std::size_t i = 0; i < SGS::L_POLYNOMIAL_DEGREE; ++i)
    {
        Polynomial<SGS::X_POLYNOMIAL_DEGREE * SGS::L_POLYNOMIAL_DEGREE> xPow =
            pow<SGS::X_POLYNOMIAL_DEGREE, SGS::X_POLYNOMIAL_DEGREE * SGS::L_POLYNOMIAL_DEGREE>(
                x, i, groupZpValues.q);
        Polynomial<SGS::L_EXP_POLYNOMIAL_DEGREE> element =
            multiply<SGS::A_POLYNOMIAL_DEGREE,
                     SGS::X_POLYNOMIAL_DEGREE * SGS::L_POLYNOMIAL_DEGREE,
                     SGS::L_EXP_POLYNOMIAL_DEGREE>(aPolys[i], xPow, groupZpValues.q);
        expandedLPolynomial = add<SGS::L_EXP_POLYNOMIAL_DEGREE,
                                  SGS::L_EXP_POLYNOMIAL_DEGREE,
                                  SGS::L_EXP_POLYNOMIAL_DEGREE>(expandedLPolynomial, element, groupZpValues.q);
    }
    return expandedLPolynomial;
}

void StepOutGroupSignaturesManager::finalizeSignature(
    const unsigned int signatureIndex,
    const FinalizeSignatureOutput& output)
{
    using namespace boost::assign;
    PendingSignature& pendingSignature = pendingSignaturesManager.getPendingSignature(signatureIndex);
    pendingSignature.finalizeSignature(output.getUserIndex(), output.getThetaPrimElement());
    if(pendingSignature.getSignersXtValues().size() == pendingSignature.getSignersThetaPrimElements().size())
    {
        const std::map<unsigned int, ThetaPrimElement>& signersThetaPrimElements =
            pendingSignature.getSignersThetaPrimElements();
        ThetaPrim thetaPrim;
        for(std::map<unsigned int, ThetaPrimElement>::const_iterator it = signersThetaPrimElements.begin();
            it != signersThetaPrimElements.end();
            ++it)
        {
            thetaPrim += it->second;
        }
        pendingSignature.setThetaPrim(thetaPrim);
    }
}

const UserPrivateKey& StepOutGroupSignaturesManager::getDummyUserPrivateKey()
{
    return *dummyUserPrivateKey;
}

const GroupZpValues& StepOutGroupSignaturesManager::getGroupZpValues() const
{
    return groupZpValues;
}

const PublishedValues& StepOutGroupSignaturesManager::getPublishedValues(const CheckProcedureInput& input)
{
    const unsigned int userIndex = input.getUserIndex();
    const BigInteger& t = input.getT();
    BOOST_ASSERT(publishedUsersSecrets.count(userIndex));
    BOOST_FOREACH(const PublishedValues& publishedValues, publishedUsersSecrets[userIndex])
    {
        if(publishedValues.getT() == t)
            return publishedValues;
    }
    BOOST_ASSERT(0);
}

const RSAKey& StepOutGroupSignaturesManager::getServerPublicKey() const
{
    return dynamic_cast<const RSAKey&>(keyPair->getPublicKey());
}

Signature StepOutGroupSignaturesManager::getSignature(const unsigned int signatureIndex)
{
    const PendingSignature& pendingSignature = pendingSignaturesManager.getPendingSignature(signatureIndex);
    return Signature(
        pendingSignature.getT(),
        pendingSignature.getX(),
        pendingSignature.getDelta(),
        pendingSignature.getThetaPrim(),
        pendingSignature.getC(),
        pendingSignature.getSigma());
}

BigInteger StepOutGroupSignaturesManager::getTFromPendingSignature(const unsigned int signatureIndex)
{
    return pendingSignaturesManager.getPendingSignature(signatureIndex).getT();
}

const UserPublicKey& StepOutGroupSignaturesManager::getUserPublicKey(const unsigned int userIndex) const
{
    BOOST_ASSERT(userIndex < usersPublicKeys.size());
    return usersPublicKeys[userIndex];
}

bool StepOutGroupSignaturesManager::hasPublishedValues(const CheckProcedureInput& input)
{
    const unsigned int userIndex = input.getUserIndex();
    const BigInteger& t = input.getT();
    if(publishedUsersSecrets.count(userIndex) == 0)
        return false;
    BOOST_FOREACH(const PublishedValues& publishedValues, publishedUsersSecrets[userIndex])
    {
        if(publishedValues.getT() == t)
            return true;
    }
    return false;
}

void StepOutGroupSignaturesManager::initializeGroup()
{
    initializeAPolynomials();
    initializeSPolynomial();
}

void StepOutGroupSignaturesManager::initializeGroupZpValues()
{
    initializePQ();
    initializeG();
}

void StepOutGroupSignaturesManager::initializeKeyPair()
{
    keyPair.reset(new RSAKeyPair(SGS::RSA_KEY_NBITS));
}

void StepOutGroupSignaturesManager::initializePQ()
{
    BigInteger::PrimeGenerator primeGenerator(SGS::COEFFICIENTS_NBITS);
    do
    {
        groupZpValues.q = primeGenerator();
        groupZpValues.p = 2 * groupZpValues.q + 1;
    }
    while(!groupZpValues.p.isPrime());
}

void StepOutGroupSignaturesManager::initializeG()
{
    groupZpValues.g.set(2u);
    while(powm(groupZpValues.g, groupZpValues.q + 1, groupZpValues.p) != groupZpValues.g)
        ++groupZpValues.g;
}

unsigned int StepOutGroupSignaturesManager::initializeSignature(const InitializeSignatureInput& input)
{
    unsigned int userIndex = input.getUserIndex();
    const std::string& message = input.getMessage();
    const BigInteger& x = input.getX();
    BigInteger t = calculateT(x, message);
    return pendingSignaturesManager.addPendingSignature(userIndex, message, t, x);
}

StepOutGroupSignaturesManager& StepOutGroupSignaturesManager::instance()
{
    return sgs;
}

void StepOutGroupSignaturesManager::joinSignature(const unsigned int signatureIndex, const JoinSignatureInput& input)
{
    pendingSignaturesManager.addUserToPendingSignature(signatureIndex, input.getUserIndex(), input.getXt());
}

void StepOutGroupSignaturesManager::publish(const PublishProcedureInput& input)
{
    publishedUsersSecrets[input.getUserIndex()].insert(input.getPublishedValues());
}

void StepOutGroupSignaturesManager::initializeAPolynomials()
{
    BOOST_FOREACH(Polynomial<SGS::A_POLYNOMIAL_DEGREE>& l_aPoly, aPolys)
        randomizePolynomial(l_aPoly);
}

void StepOutGroupSignaturesManager::initializeSPolynomial()
{
    randomizePolynomial(sPoly);
}

template<std::size_t D>
void StepOutGroupSignaturesManager::randomizePolynomial(Polynomial<D>& p_poly)
{
    std::generate(p_poly.begin(), p_poly.end(), BigInteger::RandomGenerator(SGS::COEFFICIENTS_NBITS));
    std::for_each(p_poly.begin(), p_poly.end(), boost::bind(operator%, _1, groupZpValues.q));
}

std::size_t StepOutGroupSignaturesManager::registerNewUser(const UserPublicKey& p_userPublicKey)
{
    usersPublicKeys.push_back(p_userPublicKey);
    return usersPublicKeys.size() - 1;
}

SignProcedureOutput StepOutGroupSignaturesManager::sign(const BigInteger& t,
                                                        const BigInteger& x,
                                                        const std::size_t d,
                                                        const std::string& h)
{
    // generate r from Zq at random
    BigInteger::RandomGenerator randomGenerator(SGS::COEFFICIENTS_NBITS);
    BigInteger r = randomGenerator() % groupZpValues.q;
    // calculate necessary data
    Delta delta = createDelta(t, d, r);
    C c = createC(t, x, r);
    Sigma sigma = createSigma(c, delta, h);
    return SignProcedureOutput(delta, c, sigma);
}

SignProcedureOutput StepOutGroupSignaturesManager::sign(const SignProcedureInput& input)
{
    const BigInteger& t = boost::get<0>(input);
    const BigInteger& x = boost::get<1>(input);
    const std::size_t d = boost::get<2>(input);
    const std::string& h = boost::get<3>(input);
    return sign(t, x, d, h);
}
