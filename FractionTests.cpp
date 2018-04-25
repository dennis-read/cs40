#include "Catch.h"
#include "Fraction.h"
#include <string>
#include <iostream>
#include <sstream>

// minimal checks for M0 milestone
TEST_CASE( "Fraction", "[]" ) {
   
    SECTION( "constructor, default" ) {
        Fraction f;
        // these values currently hard coded for M0
        CHECK( f.getNum() == 9999 );
        CHECK( f.getDen() == 9999 );
    }

    SECTION( "constructor, parameterized" ) {
        Fraction f(1111,2222);
        
        CHECK( f.getNum() == 1111 );
        CHECK( f.getDen() == 2222 );
    }

    SECTION( "constructor, zero denominator" ) {
        CHECK_THROWS_AS( Fraction(1111,0), invalid_argument);
        CHECK_THROWS_WITH( Fraction(1111,0), "zero denominator");
    }

    SECTION( "operator >>" ) {
        Fraction f;
        stringstream input("1/2 + 4/3");
        input >> f;

        // M0 ignores stream input and returns current object
        CHECK( f.getNum() == 9999 );
        CHECK( f.getDen() == 9999 );
    }
 
    SECTION( "isZero()" ) {
        CHECK( Fraction(0,1).isZero() == true );
        CHECK( Fraction(1,1).isZero() == false );          
    }

    SECTION( "isPositive" ) {
        CHECK( Fraction( 0, 1).isPositive() == true  );
        CHECK( Fraction( 1, 1).isPositive() == true  );      
        CHECK( Fraction(-1,-1).isPositive() == true  ); 
        CHECK( Fraction(-1, 1).isPositive() == false ); 
        CHECK( Fraction( 1,-1).isPositive() == false );                             
    }  

    SECTION( "isNegative" ) {
        CHECK( Fraction( 0, 1).isNegative() == false  );
        CHECK( Fraction( 1, 1).isNegative() == false  );      
        CHECK( Fraction(-1,-1).isNegative() == false  ); 
        CHECK( Fraction(-1, 1).isNegative() == true ); 
        CHECK( Fraction( 1,-1).isNegative() == true );                             
    }

    SECTION( "isWholeNumber" ) {
        CHECK( Fraction( 0,1).isWholeNumber() == true  );
        CHECK( Fraction( 1,1).isWholeNumber() == true  );      
        CHECK( Fraction( 1,2).isWholeNumber() == false ); 
        CHECK( Fraction( 2,1).isWholeNumber() == true  );       
        CHECK( Fraction(-2,1).isWholeNumber() == true  );                                 
    } 
  
    SECTION( "operator <<" ) {
        stringstream output;

        // handle signs
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 5, 6))).str() == "5/6" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-5, 6))).str() == "-5/6" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 5,-6))).str() == "-5/6" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-5,-6))).str() == "5/6" );
        
        // whole number
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 6, 6))).str() == "1" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-6, 6))).str() == "-1" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 6,-6))).str() == "-1" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-6,-6))).str() == "1" );
        
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 12, 6))).str() == "2" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-12, 6))).str() == "-2" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 12,-6))).str() == "-2" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-12,-6))).str() == "2" );

        // zero
        // whole number
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 0, 6))).str() == "0" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-0, 6))).str() == "0" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 0,-6))).str() == "0" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-0,-6))).str() == "0" );        
    }
                    
}