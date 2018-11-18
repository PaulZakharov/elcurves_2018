#include <iostream>
#include <ctime>

#include "cryptopp/algparam.h"
#include "cryptopp/osrng.h"
#include "cryptopp/integer.h"
#include "cryptopp/modarith.h"
#include "cryptopp/cryptlib.h"

#include "params.h"

#ifdef JACOBI
  #define HFILE "jacobi.h"
  #define BuildName "JACOBI\t"
#elif PROJECTIVE
  #define HFILE "projectivePoint.h"
  #define BuildName "PROJECTIVE"
#elif STANDART
  #define HFILE "point.h"
  #define BuildName "STANDART"
#else
  #define HFILE "point.h"
  #define BuildName "STANDART"
#endif

#include  HFILE


using namespace std;
using CryptoPP::Integer;

int main( int, char** )  
{
  clock_t start, stop;
  start = clock();
  Point generatorP, waste;
  generatorP = Point(pX, pY);
  waste = generatorP;
  for (int i = 0; i < 100000; i++)
  {
    waste = waste + generatorP;
  }
  stop = clock();
  cout << "Sum test: " << "100000 раз " <<  CURVENAME << " " << BuildName<<"\t\t" << (float)(stop - start)/ CLOCKS_PER_SEC << " в секундах" << endl;
  return 0;

}



