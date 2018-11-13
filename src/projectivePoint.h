#include "params.h"
#include <iostream>

class Point 
{
public:
	CryptoPP::Integer x;
	CryptoPP::Integer y;
	CryptoPP::Integer z;
	Point() :
	x 	(1),
	y 	(1),
	z	(1)
	{}
	Point(CryptoPP::Integer _x, CryptoPP::Integer _y, CryptoPP::Integer _z = 1) :
	x 	(_x.Modulo(p)),
	y 	(_y.Modulo(p)),
	z	(_z.Modulo(p))
	{}
	const bool operator == (const Point p1) const
	{	
		return ( 	(p1.x == x) 
				&& 	(p1.y == y) 
				&& 	(p1.z == z));
	}
	CryptoPP::Integer getX()
	{
		if (z == 0)
			return 0;
		else
			return MOD.Divide(x,z);
	}
	Point operator-() const
	{
		return Point(x, (-y).Modulo(p));
	}
	
    friend std::ostream& operator<<(std::ostream& os, const Point& pnt);
    
    Point operator+(Point const & P2) const;

    Point doubling() const;
};

std::ostream& operator << (std::ostream& os, const Point& pnt)
{
	//os << '(' << pnt.x  << "  " << pnt.y << "  " << pnt.z  << ")" << std::endl;
	if (pnt.z != 0)
	{
		os << '(' << MOD.Divide(pnt.x, pnt.z)  << "  " << MOD.Divide(pnt.y, pnt.z) << ')';
	}
	else
		os << "(inf, inf)";
	return os;
}

Point Point::operator+(Point const & pointQ) const
{
	Point pointP = (*this);
	if (pointP == pointQ)
		return pointP.doubling();
	if (pointP.z == 0)
		return pointQ;
	if (pointQ.z == 0)
		return pointP;
	if (pointP == -pointQ)
		return Point(0, 0, 0);
	CryptoPP::Integer M = (pointQ.y * pointP.z - pointP.y * pointQ.z).Modulo(p);
	CryptoPP::Integer N = (pointQ.x * pointP.z - pointP.x * pointQ.z).Modulo(p); 
	CryptoPP::Integer xCord = N *(M * M * pointP.z * pointQ.z - N * N * (pointP.x * pointQ.z + pointP.z * pointQ.x));
	CryptoPP::Integer yCord = M * (N * N * (2 * pointP.x * pointQ.z + pointQ.x * pointP.z) - M * M * pointQ.z * pointP.z) - pointP.y * pointQ.z * N * N * N;
	CryptoPP::Integer zCord = N * N * N * pointP.z * pointQ.z;
	return Point(xCord, yCord, zCord);

}

Point Point::doubling() const
{
	if (z == 0)
    	return *this;
  	if (*this == (-(*this)))
    	return Point(0, 0, 0);
    CryptoPP::Integer M = (3 * x * x + a * z * z).Modulo(p);
	CryptoPP::Integer N = (2 * y * z).Modulo(p); 
	CryptoPP::Integer xCord = N * M * M - 4 * N * N * x * y;
	CryptoPP::Integer yCord = M * N * 6 * x * y - M * M * M - 2 * N * N * y * y;
	CryptoPP::Integer zCord = N * N * N;
	return Point(xCord, yCord, zCord);


}

Point operator*(CryptoPP::Integer n, const Point &P)
{
	Point a = P;
	Point result = Point(1, 1, 0);
	if (n < 0)
	{
		std::cerr << "BAD arguments\n";
		return result;
	}

	while (n > 0)
	{
		if (n % 2 ==  0)
		{
			n = n / 2;
			a = a.doubling();
		}
		else
		{
			result = result + a;
			a = a.doubling();
			n = (n - 1) / 2;
		}
	}	
	return result;

}
