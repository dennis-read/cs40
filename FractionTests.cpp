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
        REQUIRE( f.getNum() == 9999 );
        REQUIRE( f.getDen() == 9999 );
    }

    SECTION( "constructor, parameterized" ) {
        Fraction f(1111,2222);
        
        REQUIRE( f.getNum() == 1111 );
        REQUIRE( f.getDen() == 2222 );
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
        REQUIRE( f.getNum() == 9999 );
        REQUIRE( f.getDen() == 9999 );
    }

    SECTION( "operator <<" ) {
        Fraction f(1111,2222);
        stringstream output;
        output << f;

        REQUIRE( output.str() == "1111/2222" );
    }
}