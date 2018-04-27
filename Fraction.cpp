#include"Fraction.h"

#include<iostream>
#include<stdexcept>
#include<string>
#include<regex>

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
	setState(f._num, f._den);
}

istream& operator>> (istream& is, Fraction& f)
{
	// updated for M6
	string pattern = 
		R"((\D*\d+\D*))"	// numerator	[capture:1]
		R"(/)"				// literal
		R"((\D*\d+))"		// denominator	[capture:2]
		R"(\D)";			// terminator
    regex regex(pattern);   // initialize regex with pattern
    smatch matches;         // hold evaluation results
    string input;           // built up from input stream, one char at a time
    bool matched = false;   // detect when regex expr is matched
    char c;                 // most recent character retrieved from stream
    
	// advance through stream,trying to match pattern
    do	
	{	is.get(c);
		input += c;
        matched = regex_match(input, matches, regex); 
	}  while (!matched);
	is.putback(c); // return last read character to stream

	// set state values (num, den)
	f.setState(stoi(matches[1].str()),stoi(matches[2].str())); 
	
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

Fraction& Fraction::operator+(const Fraction& f) const
{
	int num;
	int den;

	// updated for M4
	// if like fractions, just add numerators
	if (_den == f._den)
	{
		num = _num + f._num;
		den = _den;
	}
	// otherwise, use simplest common denonminator
	else
	{
		num = (_num * f._den) + (f._num * _den);
		den = (_den * f._den);
	}
	
	Fraction* result = new Fraction(num, den);
	return *result;
}

Fraction& Fraction::operator-(const Fraction& f) const
	
{
	int num;
	int den;

	// updated for M5
	// if like fractions, just add numerators
	if (_den == f._den)
	{
		num = _num - f._num;
		den = _den;
	}
	// otherwise, use simplest common denonminator
	else
	{
		num = (_num * f._den) - (f._num * _den);
		den = (_den * f._den);
	}

	Fraction* result = new Fraction(num, den);
	return *result;
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
		throw invalid_argument("division by zero");
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