#include <iostream>

#include "cryptopp/algparam.h"
#include "cryptopp/osrng.h"
#include "cryptopp/integer.h"
#include "cryptopp/modarith.h"
#include "cryptopp/cryptlib.h"

#include "params.h"
#include "point.h"


using namespace std;
using CryptoPP::Integer;




int main( int, char** )  
{
  CryptoPP::AutoSeededRandomPool rng;
  Integer message = Integer(rng, 0, 1000000000);
  Point generatorP = Point(pX, pY);
  Integer k, r, s;
Step1:
  k = Integer(rng, 0, Q - 1);                   //Выбрать случайное целое число k in [1, q-1].
  cout << k << endl;
  Point pointQ = k * generatorP;                //Вычислить k*P = (x1,y1) } r = x_1 mod q
  cout << " pointQ" << pointQ << endl;
  r = (pointQ.x).Modulo(Q);                     //и положить в r=x1 mod q
  cout << r << endl;
  if (r == 0)
    goto Step1;
  s = (message +  k * r); 
  s = MODQ.Divide(s, k);                        //положить s = k^-1(h + x * r) mod q
  cout  << s << endl;
  if (s == 0)
    goto Step1;
  

  Integer u1, u2;                               // Подпись (r,s)
  
  u1 = MODQ.Divide(message, s);
  u2 = MODQ.Divide(r, s);
  Point V = u1 * generatorP + u2 * pointQ;
  cout << "Point V" << V << endl;
  cout << "V " << V.x << endl << "r " << r << endl;
  // assert( V.x == r);
  return 0;
}



