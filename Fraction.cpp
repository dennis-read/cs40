#include"Fraction.h"

#include<iostream>
#include<stdexcept>
#include<string>
#include<regex>

using namespace std;

Fraction::Fraction()
{
	setState(1,1);
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
        R"(\s*)"    		// optional white space
        R"((-)?)"   		// optional negation for numerator      [capture: 1]
        R"(\s*)"    		// optional white space        
        R"((\d+))"  		// numerator digits                     [capture: 2]      
        R"(\s*)"    		// optional white space         
        R"(/)"      		// division symbol
        R"(\s*)"   			// optional white space  
        R"((-)?)"   		// optional negation for denominator    [capture: 3] 
        R"(\s*)"    		// optional white space          
        R"((\d+))"			// denominator digits                   [capture: 4] 
		R"(\D)"				// terminator
		;
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
	f.setState(
			stoi(matches[1].str() + matches[2].str())
		,	stoi(matches[3].str() + matches[4].str())
		); 
	
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
void Fraction::setState(int num, int den)
{
	// detect invalid denominator (zero)
	if (den == 0)
	{
		throw invalid_argument("division by zero");
	}

	// ensure that denominator is unsigned
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
	
	// reduce to simplest form
	reduce();
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

// find gcd of two numbers
int Fraction::findGCD (int n1, int n2) 
{
  int gcd, remainder;

  /* Euclid's algorithm */
  remainder = n1 % n2; 
  while ( remainder != 0 )
  {
    n1 = n2;
    n2 = remainder; 
    remainder = n1 % n2; 
  } 
  gcd = n2; 

  return abs(gcd); // ignore sign
}

// reduce to simplest form
void Fraction::reduce() 
{
  int gcd;   
  gcd = findGCD(_num, _den);
  _num = _num / gcd;
  _den = _den / gcd;
}
