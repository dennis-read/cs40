#include"Fraction.h"

#include<iostream>
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


Fraction::Fraction(const Fraction& f)
{
	setState(f.getNum(), f.getDen());
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
	// revised for M2 milestone

	// handle sign separately
	if ( f.isNegative() ) 
		os << "-";

	// whole number
	if ( f.isWholeNumber() )
	{
		os << abs(f.getQuotient());
	}
	// fraction
	else
	{
		os << abs(f._num) << "/" << abs(f._den);
	}
	return os;
}

Fraction& Fraction::operator=(const Fraction& rhs)
{	
	// updated for M3
	setState(rhs.getNum(), rhs.getDen());
	return (*this);
}

Fraction& Fraction::operator+(const Fraction& f)
{
	// minimal implementation for M0 milestone
	return (*this);
}

Fraction& Fraction::operator-(const Fraction& f)
	
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

int Fraction::getQuotient() const
{
	return _num / _den;
}

int Fraction::getRemainder() const
{
	return _num % _den;
}

bool Fraction::isZero() const
{
	return _num == 0;
}

bool Fraction::isPositive() const
{
	return 	isZero() 
		|| (_num < 0 && _den < 0)
		|| (_num > 0 && _den > 0); 
}

bool Fraction::isNegative() const
{
	return ! isPositive();
}

bool Fraction::isWholeNumber() const
{
	return isZero() || getRemainder() == 0;
}