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
  CryptoPP::AutoSeededRandomPool rng;
  Integer message = Integer(rng, 0, 1000000000);
  Point generatorP = Point(pX, pY);
  Integer k, r, s;
Step1:
  k = Integer(rng, 0, Q - 1);                   //Выбрать случайное целое число k in [1, q-1].
  //cout << k << endl;
  Point pointQ = k * generatorP;                //Вычислить k*P = (x1,y1) } r = x_1 mod q
  //cout << "pointQ" << pointQ << endl;
  r = (pointQ.getX()).Modulo(Q);                //и положить в r=x1 mod q
  //cout << "R " << r << endl;
  if (r == 0)
    goto Step1;
  s = (message +  k * r); 
  s = MODQ.Divide(s, k);                        //положить s = k^-1(h + x * r) mod q
  //cout  <<"S " <<  s << endl;
  if (s == 0)
    goto Step1;
  

  Integer u1, u2;                               // Подпись (r,s)
  
  u1 = MODQ.Divide(message, s);
  u2 = MODQ.Divide(r, s);
  Point V = u1 * generatorP + u2 * pointQ;
  //cout << "Point V" << V << endl;
  //cout << "V " << V.getX().Modulo(Q) << endl << "r " << r << endl;
  assert(V.getX().Modulo(Q) == r);
  stop = clock();
  cout << BuildName<<"\t\t" << (float)(stop - start)/ CLOCKS_PER_SEC << endl;
  return 0;
}



