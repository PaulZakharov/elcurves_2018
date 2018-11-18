#include "params.h"
#include <iostream>

class Point 
{
public:
	CryptoPP::Integer x;
	CryptoPP::Integer y;
	bool Infinity;
	Point() :
	x 	(1),
	y 	(1),
	Infinity(false)
	{}
	Point(CryptoPP::Integer _x, CryptoPP::Integer _y, bool infinity = false) :
	x 	(_x.Modulo(p)),
	y 	(_y.Modulo(p)),
	Infinity(infinity)
	{}
	const bool operator == (const Point p1) const
	{	
		return ( 	(p1.x == x)
				 && (p1.y == y));
	}
	CryptoPP::Integer getX()
	{
		if (Infinity)
			return 0;
		else
			return x;
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
	if (!pnt.Infinity)
		os << "\t X = " << pnt.x  << "\n \t Y = " << pnt.y;
	else
		os << "(inf, inf)";

	return os;
}

Point Point::operator+(Point const & P2) const
{
	Point P1 = (*this);
	if (P1 == P2)
		return P1.doubling();
	if (P1.Infinity)
		return P2;
	if (P2.Infinity)
		return P1;
	if (P1 == -P2)
		return Point(0, 0, true);
	CryptoPP::Integer t = (P2.y - P1.y).Modulo(p);
	CryptoPP::Integer z = (P2.x - P1.x).Modulo(p);
	CryptoPP::Integer x3 =  MOD.Divide(t, z);
	x3 = MOD.Square(x3);
	x3 = (x3 -  P1.x);
	x3 = (x3 -  P2.x);

	CryptoPP::Integer y3 =  MOD.Divide(t, z);
	y3 = (y3 * (P1.x - x3));
	y3 = (y3 - P1.y);
	return Point(x3, y3);
}


Point Point::doubling() const
{
	if (Infinity)
	return *this;
	if (*this == (-(*this)))
	return Point(0, 0, true);
	CryptoPP::Integer t = (3 * x * x + a).Modulo(p);
	CryptoPP::Integer z = (2 * y).Modulo(p);

	CryptoPP::Integer x3 =  MOD.Divide(t, z);
	x3 = MOD.Square(x3);
	x3 = (x3 -  2 * x);

	CryptoPP::Integer y3 =  MOD.Divide(t, z);
	y3 = y3 * (x - x3);
	y3 = (y3 - y);

	return Point(x3, y3);
}

Point operator*(CryptoPP::Integer n, const Point &P)
{
	Point a = P;
	Point result = Point(0, 0, true);
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
