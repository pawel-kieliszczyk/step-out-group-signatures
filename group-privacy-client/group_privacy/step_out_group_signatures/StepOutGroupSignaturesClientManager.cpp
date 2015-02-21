/**
 * @file StepOutGroupSignaturesClientManager.cpp
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

#include "StepOutGroupSignaturesClientManager.hpp"

#include "../digital_signature/SigitalSignatureManager.hpp"
#include "../hash/HMAC_SHA256.hpp"
#include "../hash/SHA256.hpp"
#include "../key/RSAKey.hpp"
#include "../mpi/BigInteger.hpp"
#include "Utils.hpp"

#include <boost/assign.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include <algorithm>
#include <cstddef>

StepOutGroupSignaturesClientManager StepOutGroupSignaturesClientManager::manager;

StepOutGroupSignaturesClientManager::StepOutGroupSignaturesClientManager()
    : registered(false)
{
}

CheckProcedureInput StepOutGroupSignaturesClientManager::createCheckProcedureInput(const unsigned int index,
                                                                                   const Signature& signature)
{
    return CheckProcedureInput(index, signature.getT());
}

CloseSignatureInput StepOutGroupSignaturesClientManager::createCloseSignatureInput(const unsigned int signatureIndex)
{
    BOOST_ASSERT(userIndex);
    return CloseSignatureInput(*userIndex, signatureIndex);
}

FinalizeSignatureOutput StepOutGroupSignaturesClientManager::createFinalizeProcedureOutput(
    const FinalizeSignatureInput& input)
{
    BigInteger xt = userPrivateKey->getX()(input.getT(), groupZpValues->q);
    BigInteger grPt = powm(
        input.getGr(),
        userPrivateKey->getP()(input.getT(), groupZpValues->q),
        groupZpValues->p);
    BigInteger gQtrSt = powm(
        userPrivateKey->getQ()(input.getT(), groupZpValues->p),
        input.getRSt(),
        groupZpValues->p);
    return FinalizeSignatureOutput(*userIndex, ThetaPrimElement(xt, grPt, gQtrSt));
}

InitializeSignatureInput StepOutGroupSignaturesClientManager::createInitializeSignatureInput(const std::string& message)
{
    BigInteger::RandomGenerator randGen(SGS::COEFFICIENTS_NBITS);
    return InitializeSignatureInput(*userIndex, message, randGen() % groupZpValues->p);
}

JoinSignatureInput StepOutGroupSignaturesClientManager::createJoinSignatureInput(const BigInteger& t)
{
    BOOST_ASSERT(userIndex);
    BOOST_ASSERT(userPrivateKey);
    return JoinSignatureInput(*userIndex, userPrivateKey->getX()(t, groupZpValues->q));
}

const UserPublicKey& StepOutGroupSignaturesClientManager::createKeys(const PQPolynomials& polynomials)
{
    userPrivateKey->setP(polynomials.getP());
    userPrivateKey->setQ(polynomials.getQ());
    randomizePolynomial(userPrivateKey->getM());
    userPublicKey->setQm(PolynomialInTheExponent<SGS::QM_POLYNOMIAL_DEGREE>(userPrivateKey->getQ(),
                                                                            userPrivateKey->getM(),
                                                                            groupZpValues->p));
    return *userPublicKey;
}

Psi StepOutGroupSignaturesClientManager::createPsi(const Delta& delta,
                                                   const Theta& theta,
                                                   const PsiElement& psiElement) const
{
    Psi psi;
    BOOST_FOREACH(const DeltaElement& deltaElement, delta)
        psi.push_back(PsiElement(deltaElement.i(), deltaElement.grLti()));
    BOOST_FOREACH(const ThetaElement& thetaElement, theta)
        psi.push_back(PsiElement(boost::get<0>(thetaElement), boost::get<1>(thetaElement)));
    psi.push_back(psiElement);
    return psi;
}

PublishProcedureInput StepOutGroupSignaturesClientManager::createPublishProcedureInput(
    const Signature& signature) const
{
    const BigInteger& t = signature.getT();
    BigInteger xt = userPrivateKey->getX()(t, groupZpValues->q);
    BigInteger Pt = userPrivateKey->getP()(t, groupZpValues->q);
    BigInteger mt = userPrivateKey->getM()(t, groupZpValues->q);
    PublishedValues publishedValues(t, xt, Pt, mt);
    return PublishProcedureInput(*userIndex, publishedValues);
}

Signature StepOutGroupSignaturesClientManager::createSignature(const SignProcedureInput& input,
                                                               const SignProcedureOutput& output)
{
    ThetaPrim thetaPrim = createThetaPrim(input, output);
    return Signature(input.getT(), input.getX(), output.getDelta(), thetaPrim, output.getC(), output.getSigma());
}

ThetaPrim StepOutGroupSignaturesClientManager::createThetaPrim(const SignProcedureInput& input, const SignProcedureOutput& output)
{
    BigInteger firstThetaPrimElement = userPrivateKey->getX()(input.getT(), groupZpValues->q);
    const C& c = output.getC();
    BigInteger secondThetaPrimElement = powm(c.gr(),
                                        userPrivateKey->getP()(input.getT(), groupZpValues->q),
                                        groupZpValues->p);
    BigInteger thirdThetaPrimElement = powm(userPrivateKey->getQ()(input.getT(), groupZpValues->p),
                                            c.rSt(),
                                            groupZpValues->p);
    ThetaPrim thetaPrim;
    thetaPrim.push_back(ThetaPrimElement(firstThetaPrimElement, secondThetaPrimElement, thirdThetaPrimElement));
    return thetaPrim;
}

const SignProcedureInput StepOutGroupSignaturesClientManager::createSignProcedureInput(
    const std::string& messageToSign)
{
    BigInteger::RandomGenerator randomGen(SGS::COEFFICIENTS_NBITS);
    BigInteger x = randomGen() % groupZpValues->p;
    HMAC_SHA256 keyedHasher;
    keyedHasher.setKey(x.toString());
    keyedHasher.setText(messageToSign);
    BigInteger t(keyedHasher.getHexHash());
    t %= groupZpValues->q;
    BigInteger Z = userPrivateKey->getX()(t, groupZpValues->q);
    SHA256 hasher;
    hasher.setText(messageToSign + Z.toString());
    std::string h = hasher.getHexHash();
    std::size_t d = 1;
    return SignProcedureInput(t, x, d, h);
}

Theta StepOutGroupSignaturesClientManager::createTheta(const ThetaPrim& thetaPrim) const
{
    Theta theta;
    BOOST_FOREACH(const ThetaPrimElement& thetaPrimElement, thetaPrim)
        theta.push_back(createThetaElement(thetaPrimElement));
    return theta;
}

ThetaElement StepOutGroupSignaturesClientManager::createThetaElement(const ThetaPrimElement& thetaPrimElement) const
{
    return ThetaElement(boost::get<0>(thetaPrimElement),
                        (boost::get<1>(thetaPrimElement) * boost::get<2>(thetaPrimElement)) % groupZpValues->p);
}

void StepOutGroupSignaturesClientManager::initializeUserKeys()
{
    userPrivateKey.reset(new UserPrivateKey);
    userPublicKey.reset(new UserPublicKey);
    randomizePolynomial(userPrivateKey->getX());
}

std::string StepOutGroupSignaturesClientManager::getUserIndex() const
{
    return (registered ? boost::lexical_cast<std::string>(*userIndex) : "?");
}

const Polynomial<SGS::X_POLYNOMIAL_DEGREE>& StepOutGroupSignaturesClientManager::getXPolynomial() const
{
    return userPrivateKey->getX();
}

StepOutGroupSignaturesClientManager& StepOutGroupSignaturesClientManager::instance()
{
    return manager;
}

bool StepOutGroupSignaturesClientManager::isNotSigner(const UserPublicKey& publicKey,
                                                      const PublishedValues& publishedValues,
                                                      const Signature& signature) const
{
    if(isSigner(publicKey, publishedValues, signature))
        return false;
    BigInteger gQt = powm(publicKey.getQm()(publishedValues.getT(), groupZpValues->p),
                          invm(publishedValues.getMt(), groupZpValues->q),
                          groupZpValues->p);
    BigInteger grLtxt = (powm(signature.getC().gr(), publishedValues.getPt(), groupZpValues->p)
                         * powm(gQt, signature.getC().rSt(), groupZpValues->p)) % groupZpValues->p;
    Psi psi = createPsi(signature.getDelta(),
                        createTheta(signature.getThetaPrim()),
                        PsiElement(publishedValues.getXt(), grLtxt));
    std::vector<BigInteger> args, values;
    BOOST_FOREACH(const PsiElement& psiElement, psi)
    {
        args.push_back(boost::get<0>(psiElement));
        values.push_back(boost::get<1>(psiElement));
    }
    BigInteger grLPrim = PolynomialInTheExponentUtils::interpolatePolynomialInPoint(args,
                                                                                    values,
                                                                                    signature.getX(),
                                                                                    groupZpValues->p);
    return (grLPrim == signature.getC().grLtx());
}

bool StepOutGroupSignaturesClientManager::isSigner(const UserPublicKey& publicKey,
                                                   const PublishedValues& publishedValues,
                                                   const Signature& signature) const
{
    BigInteger gQt = powm(publicKey.getQm()(publishedValues.getT(), groupZpValues->p),
                          invm(publishedValues.getMt(), groupZpValues->q),
                          groupZpValues->p);
    BigInteger grLtxt = (powm(signature.getC().gr(), publishedValues.getPt(), groupZpValues->p)
                         * powm(gQt, signature.getC().rSt(), groupZpValues->p)) % groupZpValues->p;
    ThetaElement thetaElement(publishedValues.getXt(), grLtxt);
    Theta theta = createTheta(signature.getThetaPrim());
    return (std::find(theta.begin(), theta.end(), thetaElement) != theta.end());
}

template<std::size_t D>
void StepOutGroupSignaturesClientManager::randomizePolynomial(Polynomial<D>& p_poly)
{
    std::generate(p_poly.begin(), p_poly.end(), BigInteger::RandomGenerator(SGS::COEFFICIENTS_NBITS));
    std::for_each(p_poly.begin(), p_poly.end(), boost::bind(operator%, _1, groupZpValues->p));
}

void StepOutGroupSignaturesClientManager::setDummyUserPrivateKey(const UserPrivateKey& dummyUserPrivateKey)
{
    this->dummyUserPrivateKey.reset(new UserPrivateKey(dummyUserPrivateKey));
}

void StepOutGroupSignaturesClientManager::setGroupZpValues(const GroupZpValues& groupZpValuesInit)
{
    groupZpValues.reset(new GroupZpValues(groupZpValuesInit));
}

void StepOutGroupSignaturesClientManager::setServerPublicKey(const IKey& serverPublicKeyInit)
{
    serverPublicKey.reset(new RSAKey(dynamic_cast<const RSAKey&>(serverPublicKeyInit)));
}

void StepOutGroupSignaturesClientManager::setUserIndex(const unsigned int userIndexInit)
{
    userIndex.reset(new unsigned int(userIndexInit));
    registered = true;
}

bool StepOutGroupSignaturesClientManager::verifyInterpolation(const Signature& signature)
{
    BigInteger xt = dummyUserPrivateKey->getX()(signature.getT(), groupZpValues->q);
    BigInteger Pt = dummyUserPrivateKey->getP()(signature.getT(), groupZpValues->q);
    BigInteger Qt = dummyUserPrivateKey->getQ()(signature.getT(), groupZpValues->p);
    BigInteger grL = (powm(signature.getC().gr(), Pt, groupZpValues->p)
                      * powm(Qt, signature.getC().rSt(), groupZpValues->p)) % groupZpValues->p;
    Psi psi = createPsi(signature.getDelta(), createTheta(signature.getThetaPrim()), PsiElement(xt, grL));
    std::vector<BigInteger> args, values;
    BOOST_FOREACH(const PsiElement& psiElement, psi)
    {
        args.push_back(boost::get<0>(psiElement));
        values.push_back(boost::get<1>(psiElement));
    }
    BigInteger grLPrim =
        PolynomialInTheExponentUtils::interpolatePolynomialInPoint(args, values, signature.getX(), groupZpValues->p);
    return (signature.getC().grLtx() == grLPrim);
}

bool StepOutGroupSignaturesClientManager::verifyMessageHash(const std::string& message, const Signature& signature)
{
    HMAC_SHA256 keyedHasher;
    keyedHasher.setKey(signature.getX().toString());
    keyedHasher.setText(message);
    BigInteger tPrim(keyedHasher.getHexHash());
    tPrim %= groupZpValues->q;
    return (signature.getT() == tPrim);
}

bool StepOutGroupSignaturesClientManager::verifySignature(const std::string& message, const Signature& signature)
{
    return (verifySigma(message, signature) &&
            verifyMessageHash(message, signature) &&
            verifyInterpolation(signature));
}

bool StepOutGroupSignaturesClientManager::verifySigma(const std::string& message, const Signature& signature)
{
    std::string h = createH(message, signature.getThetaPrim());
    std::string strC = Utils::createString(signature.getC());
    std::string strDelta = Utils::createString(signature.getDelta());
    SHA256 hasher;
    hasher.setText(strC + strDelta + h);
    return DigitalSignatureManager::verify(hasher.getHash(),
                                           hasher.getHashLength(),
                                           signature.getSigma(),
                                           *serverPublicKey);
}

std::string StepOutGroupSignaturesClientManager::createH(const std::string& message, const ThetaPrim& thetaPrim)
{
    using namespace boost::assign;
    std::vector<BigInteger> xtValues;
    BOOST_FOREACH(const ThetaPrimElement& element, thetaPrim)
        xtValues += element.xt();
    std::sort(xtValues.begin(), xtValues.end());
    std::string Z = "";
    BOOST_FOREACH(const BigInteger& xt, xtValues)
        Z += xt.toString();
    SHA256 hasher1;
    hasher1.setText(message + Z);
    return hasher1.getHexHash();
}
