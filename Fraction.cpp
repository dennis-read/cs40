#include"Fraction.h"

#include<stdexcept>
#include<string>

using namespace std;

Fraction::Fraction()
{
	// fake values for M1 milestone
	setState(9999,9999);
}

Fraction::Fraction(int num, int den)
{
	setState(num, den);
}

istream& operator>> (istream& is, Fraction& f)
{
	// minimal implementation for M0 milestone

	// consume stream up to next operator
	char c;
	while (	is.get(c) 
			&& 	
			!(is.eof() || c == '\n' || c == '+' || c == '-'));
	
	// give operator to driver program
	is.putback(c); 

	// return fraction
	return is;
}

ostream& operator << (ostream& os, const Fraction& f)
{
	// minimal implementation for M0 milestone
	os << f.getNum() << "/" << f.getDen();
	return os;
}

Fraction& Fraction::operator=(const Fraction& rhs)
{	
	// minimal implementation for M0 milestone
	return (*this);
}

Fraction Fraction::operator+(const Fraction& f)
{
	// minimal implementation for M0 milestone
	return (*this);
}

Fraction Fraction::operator-(const Fraction& f)
	
{
	// minimal implementation for M0 milestone
	return (*this);
}

int Fraction::getNum() const
{
	return _num;
}

int Fraction::getDen() const
{
	return _den;
}

// central setting for state (numerator and denominator)
// this will eventually be used to handle simplification
void Fraction::setState(int num, int den)
{
	if (den == 0)
	{
		throw invalid_argument("zero denominator");
	}

	_num = num;
	_den = den;
}