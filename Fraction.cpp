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
	// revised for M4 milestone

	// whole number
	if ( f.isWholeNumber()  )
	{
		os << (f.getQuotient());
	}
	// fraction
	else
	{
		os << f._num << "/" << f._den;
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
	// updated for M4
	// if like fractions, just add numerators
	if (_den == f._den)
	{
		_num += f._num;
	}
	// otherwise, use simplest common denonminator
	else
	{
		_num = (_num * f._den) + (f._num * _den);
		_den = (_den * f._den);
	}
	return (*this);
}

Fraction& Fraction::operator-(const Fraction& f)
	
{
	// updated for M5
	// if like fractions, just add numerators
	if (_den == f._den)
	{
		_num -= f._num;
	}
	// otherwise, use simplest common denonminator
	else
	{
		_num = (_num * f._den) - (f._num * _den);
		_den = (_den * f._den);
	}
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
//     - detect invalid denominator (zero)
//     - ensure that denominator is unsigned
//     - reduce to simplest form
void Fraction::setState(int num, int den)
{
	if (den == 0)
	{
		throw invalid_argument("zero denominator");
	}
	if (den < 0)
	{
		_num = num * -1;
		_den = den * -1;
	}
	else
	{
		_num = num;
		_den = den;
	}
}

int Fraction::getQuotient() const
{
	return _num / _den;
}

int Fraction::getRemainder() const
{
	return _num % _den;
}

bool Fraction::isWholeNumber() const
{
	return ( getRemainder() == 0 );
}