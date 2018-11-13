#ifndef __PARAMS__
#define __PARAMS__

#include "cryptopp/integer.h"
#include "cryptopp/modarith.h"

CryptoPP::Integer p 			= CryptoPP::Integer("57896044618658097711785492504343953926634992332820282019728792003956564821041");
CryptoPP::Integer a 			= CryptoPP::Integer("7");
CryptoPP::Integer b 		    = CryptoPP::Integer("43308876546767276905765904595650931995942111794451039583252968842033849580414");
CryptoPP::Integer Q 			= CryptoPP::Integer("57896044618658097711785492504343953927082934583725450622380973592137631069619");
CryptoPP::Integer pX 			= 2;
CryptoPP::Integer pY 			= CryptoPP::Integer("4018974056539037503335449422937059775635739389905545080690979365213431566280");
CryptoPP::ModularArithmetic MOD = CryptoPP::ModularArithmetic(p); 
CryptoPP::ModularArithmetic MODQ = CryptoPP::ModularArithmetic(Q); 


#endif