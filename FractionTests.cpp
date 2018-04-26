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

    SECTION( "constructor, copy" ) {
            Fraction f = Fraction(1,2);
            CHECK( f.getNum() == 1 );
            CHECK( f.getDen() == 2 );                      
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
 
    SECTION( "getQuotient()" ) {
        CHECK( Fraction(0,1).getQuotient() == 0 );
        CHECK( Fraction(1,2).getQuotient() == 0 );        
        CHECK( Fraction(2,2).getQuotient() == 1 );
        CHECK( Fraction(4,2).getQuotient() == 2 );            
    }
    
    SECTION( "getRemainder()" ) {
        CHECK( Fraction(0,1).getRemainder() == 0 );
        CHECK( Fraction(1,2).getRemainder() == 1 );        
        CHECK( Fraction(2,2).getRemainder() == 0 );
        CHECK( Fraction(4,2).getRemainder() == 0 );            
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
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 0, 6))).str() == "0" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-0, 6))).str() == "0" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 0,-6))).str() == "0" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-0,-6))).str() == "0" );     
    }

    SECTION( "operator =" ) {
            Fraction f;
            f = Fraction(1,2);
            CHECK( f.getNum() == 1 );
            CHECK( f.getDen() == 2 );                      
    }     
    
    SECTION( "operator +" ) {
            Fraction f1 = Fraction(1,3) + Fraction(1,3);
            CHECK( f1.getNum() == 2 );
            CHECK( f1.getDen() == 3 );

            Fraction f2 = Fraction(1,3) + Fraction(1,4);
            CHECK( f2.getNum() ==  7 );
            CHECK( f2.getDen() == 12 );

            Fraction f3 = Fraction(1,3) + Fraction(-1,3);
            CHECK( f3.getNum() ==  0 );
            CHECK( f3.getDen() ==  3 );  

            Fraction f4 = Fraction(1,3) + Fraction(1,-3);
            CHECK( f4.getNum() ==  0 );
            CHECK( f4.getDen() ==  3 );            
    }  

    SECTION( "operator -" ) {
            Fraction f1 = Fraction(2,3) - Fraction(1,3);
            CHECK( f1.getNum() ==  1 );
            CHECK( f1.getDen() ==  3 );

            Fraction f2 = Fraction(1,3) - Fraction(2,3);
            CHECK( f2.getNum() == -1 );
            CHECK( f2.getDen() ==  3 );

            Fraction f3 = Fraction(1,3) - Fraction(1,4);
            CHECK( f3.getNum() ==  1 );
            CHECK( f3.getDen() ==  12 );  

            Fraction f4 = Fraction(1,3) - Fraction(2,4);
            CHECK( f4.getNum() ==  -2 );
            CHECK( f4.getDen() ==  12 );            
    }              
}