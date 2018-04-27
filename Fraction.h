#ifndef FRACTION_H
#define FRACTION_H

#include <istream>

using namespace std;

class Fraction
{        
	public:
		//Constructors
		explicit Fraction();
		explicit Fraction(int num, int den);
		Fraction(const Fraction&);

        
        // Operators
		friend istream& operator >>(istream&, Fraction&);
		friend ostream& operator <<(ostream&, const Fraction&);

		Fraction& operator =(const Fraction&);
		Fraction& operator +(const Fraction&) const; 
		Fraction& operator -(const Fraction&) const;
        
        // Accessors
		int getNum() 	const;
		int getDen()	const;

		// Helpers
		int getQuotient() 		const;
		int getRemainder()		const;

		//bool isZero() 			const;
		bool isWholeNumber()	const;

	private: 
		int  _num;
		int  _den; 

		void setState(int num, int den);
}; 

#endif 