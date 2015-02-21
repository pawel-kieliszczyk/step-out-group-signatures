/**
 * @file SHA256.hpp
 * @author Pawel Kieliszczyk <pawel.kieliszczyk@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * @section DESCRIPTION
 *
 * This file contains a definition of Secure Hash Algorithm 256
 * with the Hash-based Message Authentication Code feature.
 */

#ifndef SHA256_HPP
#define	SHA256_HPP

#include "BasicHashFunction.hpp"

typedef BasicHashFunction<GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE> SHA256;

#endif // SHA256_HPP
