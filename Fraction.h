#ifndef FRACTION_H
#define FRACTION_H

#include <istream>

using namespace std;

class Fraction
{        
	public:
		//Constructor
		explicit Fraction();
		explicit Fraction(int num, int den);

        
        // Operators
		friend istream& operator >>(istream&, Fraction&);
		friend ostream& operator <<(ostream&, const Fraction&);

		Fraction& operator =(const Fraction&);
		Fraction  operator +(const Fraction&); 
		Fraction  operator -(const Fraction&);
        
        // Accessors
		int getNum() const;
		int getDen( )const;

	private: 
		int _num;
		int _den;
}; 

#endif 