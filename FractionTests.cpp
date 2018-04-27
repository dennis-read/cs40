#include "Catch.h"
#include "Fraction.h"
#include <string>
#include <iostream>
#include <sstream>

TEST_CASE("Default constructor","[]") {
    
    SECTION( "returns hard coded values" ) {
        Fraction f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 1 );
    }
}

TEST_CASE("Parameterized constructor","[]") {
    
    SECTION( "throws exception on zero denominator" ) {
        CHECK_THROWS_AS( Fraction(1111,0), invalid_argument);
        CHECK_THROWS_WITH( Fraction(1111,0), "division by zero");
    }

    SECTION( "simplifies when common factors exists" ) {
        Fraction f(2,4);
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );
    }
    
    SECTION( "flips numerator sign when denominator is negative" ) {
        Fraction f(1,-2);
        CHECK( f.getNum() == -1 );
        CHECK( f.getDen() ==  2 );
    }
    
    SECTION( "returns arguments unchanged if already simplified with no denominator sign" ) {
        Fraction f(1,1);
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 1 );
    }
}

TEST_CASE( "Copy constructor", "[]" ) {

    SECTION( "produces exact copy of source" ) {
            Fraction src = Fraction(1,2);
            Fraction cpy(src);
            CHECK( cpy.getNum() == src.getNum() );
            CHECK( cpy.getDen() == src.getDen() );                      
        }    
}

TEST_CASE( "Operator =", "[]" ) {

    SECTION( "produces exact copy of source" ) {
            Fraction src = Fraction(1,2);
            Fraction cpy = Fraction();
            cpy = src;
            CHECK( cpy.getNum() == src.getNum() );
            CHECK( cpy.getDen() == src.getDen() );                      
        }   
}

TEST_CASE( "Operator +", "[]" ) {
   
    SECTION( "adds numerators for like fraction" ) {
            Fraction sum = Fraction(1,3) + Fraction(1,3);
            CHECK( sum.getNum() == 2 );
            CHECK( sum.getDen() == 3 );
    }

    SECTION( "respects addition of negative values" ) {
            Fraction sum = Fraction(1,3) + Fraction(-2,3);
            CHECK( sum.getNum() == -1 );
            CHECK( sum.getDen() ==  3 );
    }
    
    SECTION( "converts to simplest common denominator for unlike fraction" ) {
            Fraction sum = Fraction(1,2) + Fraction(2,3);
            CHECK( sum.getNum() == 7 );
            CHECK( sum.getDen() == 6 );
    }
    
    SECTION( "leaves addends unchanged" ) {
            Fraction x = Fraction(2,3);
            Fraction y = Fraction(1,3);
            x + y;
            CHECK( x.getNum() ==  2 );
            CHECK( x.getDen() ==  3 ); 
            CHECK( y.getNum() ==  1 );
            CHECK( y.getDen() ==  3 ); 
    }   
}

TEST_CASE( "Operator -", "[]" ) {
   
    SECTION( "subtracts numerators for like fraction" ) {
            Fraction diff = Fraction(2,3) - Fraction(1,3);
            CHECK( diff.getNum() == 1 );
            CHECK( diff.getDen() == 3 );
    }

    SECTION( "respects addition of negative values" ) {
            Fraction diff = Fraction(1,3) - Fraction(-1,3);
            CHECK( diff.getNum() == 2 );
            CHECK( diff.getDen() == 3 );
    }
    
    SECTION( "converts to simplest common denominator for unlike fraction" ) {
            Fraction diff = Fraction(2,3) - Fraction(1,2);
            CHECK( diff.getNum() == 1 );
            CHECK( diff.getDen() == 6 );
    }
    
    SECTION( "leaves subtrahends unchanged" ) {
            Fraction x = Fraction(2,3);
            Fraction y = Fraction(1,3);
            x - y;
            CHECK( x.getNum() ==  2 );
            CHECK( x.getDen() ==  3 ); 
            CHECK( y.getNum() ==  1 );
            CHECK( y.getDen() ==  3 ); 
    }   
}

TEST_CASE( "getQuotient()", "[]" ) {

    SECTION( "returns result of integer division" ) {
        CHECK( Fraction(0,2).getQuotient() == 0 );
        CHECK( Fraction(1,2).getQuotient() == 0 );        
        CHECK( Fraction(2,2).getQuotient() == 1 );
        CHECK( Fraction(3,2).getQuotient() == 1 );        
        CHECK( Fraction(4,2).getQuotient() == 2 );            
    } 
}

TEST_CASE( "getRemainder()", "[]" ) {

    SECTION( "returns remainder of integer division" ) {
        CHECK( Fraction(0,2).getRemainder() == 0 );
        CHECK( Fraction(1,2).getRemainder() == 1 );        
        CHECK( Fraction(2,2).getRemainder() == 0 );
        CHECK( Fraction(3,2).getRemainder() == 1 );            
        CHECK( Fraction(4,2).getRemainder() == 0 );            
    } 
}

TEST_CASE( "isWholeNumber()", "[]" ) {

    SECTION( "is true for zero numerator" ) {
        CHECK( Fraction( 0,1).isWholeNumber() == true );                              
    }

    SECTION( "is true for fractions that divide evenly" ) {
        CHECK( Fraction( 1,1).isWholeNumber() == true );
        CHECK( Fraction( 2,1).isWholeNumber() == true );      
                                   
    }
    
    SECTION( "is false for fractions that don't divide evenly" ) {
        CHECK( Fraction( 1,2).isWholeNumber() == false );
        CHECK( Fraction( 3,2).isWholeNumber() == false );                                     
    }   

    SECTION( "is indifferent to numerator sign" ) {
        CHECK( Fraction( 1,1).isWholeNumber() == true  );
        CHECK( Fraction(-1,1).isWholeNumber() == true  );
        CHECK( Fraction( 1,2).isWholeNumber() == false );
        CHECK( Fraction(-1,2).isWholeNumber() == false );                                               
    }        
}

TEST_CASE( "operator <<", "[]" ) {
    stringstream output;
    
    SECTION( "zero renders as zero" ) {
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 0, 1))).str() == "0" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-0, 1))).str() == "0" );         
    }

    SECTION( "whole number renders just the quotient" ) {
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 1, 1))).str() ==  "1" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-1, 1))).str() == "-1" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 2, 1))).str() ==  "2" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-2, 1))).str() == "-2" );
    }

    SECTION( "non whole number reders as fraction" ) {
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 1, 2))).str() ==  "1/2" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-1, 2))).str() == "-1/2" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction( 5, 6))).str() ==  "5/6" );
        CHECK( static_cast<std::ostringstream&>(operator<<(stringstream(), Fraction(-5, 6))).str() == "-5/6" );        
    }                             
}

TEST_CASE( "operator >>", "[]" ) {
    
    Fraction f;
 
    SECTION( "input terminated by space, operator (+-), or newline" ) {
        stringstream("1/2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );

        stringstream("1/2+") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );

        stringstream("1/2-") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );       

        stringstream("1/2\n") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );          
    }    
     
    SECTION( "numerator sign is optional" ) {
        stringstream("1/2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );

        stringstream("-1/2 ") >> f;
        CHECK( f.getNum() == -1 );
        CHECK( f.getDen() ==  2 );        
    }

    SECTION( "denominator sign is optional" ) {
        stringstream("1/2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );

        stringstream("1/-2 ") >> f;
        CHECK( f.getNum() == -1 );
        CHECK( f.getDen() ==  2 );        
    }   

    SECTION( "whitespace is ignored" ) {
        stringstream("-1/-2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );      

        stringstream(" -1/-2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );

        stringstream(" - 1/-2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );

        stringstream(" - 1 /-2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );

        stringstream(" - 1 / -2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );

        stringstream(" - 1 / - 2 ") >> f;
        CHECK( f.getNum() == 1 );
        CHECK( f.getDen() == 2 );
    }                                                                                                           
}