# CS40 HW1 - Fractions 

Simple implementation, built up through milestones.  

Proposed themes:

* M0 - Scaffold
* M1 - Constructors
* M2 - operator <<
* M3 - operator = 
* M4 - operator +
* M5 - operator -
* M6 - operator >>
* M7 - reduced fractions

The initial ordering minimizes dependencies.  These may change as work proceeds.

Work is managed in a git repository, with each milestone linked to a label.



# Goals

Develop good habits by following best practices.

1. Borrow from the agile mindset

        
        Always be able to build, run, package, and deploy.
        
        Initial M0 implementation is trivial, and known to be incorrect.
                
                But it still builds and runs.  
                
                All unit tests pass, all acceptance tests fail.
                
        Subsequent milestones target additional acceptance tests for passage.

2. Apply test-driven development

        Write unit tests for each feature.

        Automate acceptance tests using provided input/output pairs.

3. Create useful abstractions

        Fractions have a definite vocabulary, including:
                
                Numerator, Denominator
                
                Quotient, Remainder
                
                Number types (whole, mixed) 
                
                Fraction types (Proper, Improper, Reduced)
        
        Our requirements use some of these terms, so they should be visible in the code.

4. Use platform services

        For example:
                
                Leverage regular expressions, instead of writing a parser.
                
                Use tools like diff to automate acceptance tests.

# Milestones

At completion of each milestone
* A new git label will snapshot the repository state

* The notes section below will be updated with results

## M0 - Scaffold
### Goals
* Fraction header file

        Define all pubic operations (the API)
        
        Create only those private members needed for M0 scaffolding

* Fraction implementation file

        Create trivial implementations sufficient for driver programs to build and execute

* Unit Testing

        Set up Catch2 framework (single object file generated from single header file)
        
        Create FractionTests class with sample unit tests covering M0 behavior

        Hook unit tests into makefile

* Acceptance Testing

        Create subdirectories to hold samples (input and output) and execution results (output)
        
        Create script to 
                
                run sample inputs through driver program
                
                compare outputs (sample to actual) using diff
        
        Hook script into makefile

* Makefile

        Add targets for packaging and testing
                
                make package (tar command)
                
                make test-unit (call FractionTests executable)
                
                make test-acceptance (call shell script)

* Git repository 

        Initialize repo with M0 content
        
        Author README.md (this file)

### Results

* Fraction class
        
        Created header and implemenation files
        
        Minimal implementation, sufficient build and run driver programs 
                calculator, useFraction

* Testing

        Created FractionTests class based on Catch2 framework
                simple tests define and validate current behavior
                all unit tests pass
        
        Created script to 
                run driver program against sample input
                and compare results to sample output (using diff)
                all acceptance test fail (as expected)
        

* Makefile
        
        Updated to build FractionTests, and to run unit and acceptance tests
        
        Added target to build tar file

* README.md
        
        Set up content for goals and milestones

## M1 - Constructor
### Goals
* Create a centralized setter function for state management
        
        This will eventually handle validation (zero divisor) and reduction

* Update all constructors use use the setter function

* Select default state values (numerator, denominator) for default constructor

        The values have no real meaning, since the constructed objects are transient
                
### Results

* Global setter function created

        both constructors use it
        the default constructor passes 9999/9999

        setter function throws invalid_argument on zero denominator

* Unit test updated with test case for exception

        check exception type (invalid_argument)
        message (zero denominator)

* Updated makefile target for test-unit

        updated command to ./FractionTests
        explicit path to pwd is required
## M2 - operator << (insertion)
### Goals
* Revise insertion operator

* Produce formatted output per the requirements

        Cases include handling based on
        
                value 
                        zero
                        
                        proper fraction
                        
                        whole number
                        
                        mixed number
                sign
                        positive and negative


### Results

* Added helper functions

        isZero(), isPositive(), isNegative(), isWholeNumber()

        also added test cases for each

* Updated implementation of operator<<

        output varies on three conditions
                zero
                whole number
                fraction
        
        original plan included mixed numbers
                but this isn't a requirement

* Updated check-samples.sh script that implements acceptance tests

        simpify usage of diff
                use option to compare two directories
                eliminate for loop

        add summary output before detailed comparisons

* Test results

        all unit test pass
        
        all acceptance tests still fail
                this because of reliance on operator>>
        
        useFraction still works
                output reliant on operator>> is incorrect

## M3 - operator =
### Goals
* Revise assignment operator

* Direct state changes to common setter function


### Results

* implemented operator =

        makes call to setState()

* also added copy constructor with equivalent behavior

* refactored quotient and remainder properties into member functions
        
        this simplifies setState

* added FractionTests to make all target

* Test results

        all unit test pass
        
        all acceptance tests still fail
                this because of reliance on operator>>
        
        useFraction still works
                output reliant on operator>> is incorrect


## M4 - operator +
### Goals
* Revise addition operator

* Direct state changes to common setter function

* Handle fractions with unlike denominators

### Results
        
* implemented operator +
        
        used simplest common denominator for non-like fractions

        updated setState to hold negation in the numerator
                constructors can accept negative denominators
                but they're always stored as positive
                        numerator sign flipped as needed
                this greatly simplifies other operations

        retired several helper functions
                isPositive, isNegative, isZero

* tried to switch _den member variable to unsigned int

        this telegraphs the numerator's role in negation
        
        but it causes problems with the % operator:
                int % uint returns unexpected values
                so this will be revisited later


* Test results

        all unit test pass
        
        all acceptance tests still fail
                this because of reliance on operator>>
        
        useFraction still works
                output reliant on operator>> is incorrect

## M5 - operator-
### Goals
* Revise subtraction operator

* Direct state changes to common setter function

* Handle fractions with unlike denominators

### Results

* implemented operator -

        basically a clone of operator +

        possibly some common code that could be refactored here

* Test results

        all unit test pass
        
        all acceptance tests still fail
                this because of reliance on operator>>
        
        useFraction still works
                output reliant on operator>> is incorrect


## M6 - operator >> (extraction)
### Goals
* Revise extraction operator

* Parse state elements from iostream 

        numerator
                optional sign
                1 or more digits
        denominator
                optional sign
                1 or more digits

        favor use of regex over hand written state machine

* Use common setter function

### Results
        
* implemented operator >>

        pull one character at a time from input stream

        try to extract numerator and denominator using regex

        upon match
                return last character to stream
                call setState with numerator and denominator

* fixed operator+ and operator-

        noticed an issue running useFraction
        addition and subtraction were modifying *this
                instead of return new object
        corrected error and specified both operators as const
                this would have detected this issue 
        added test cases to validate no change to operands

* noticed discrepancy between sample file and assignment

        exception text on zero denominator case differs
                assignment  : [zero denominator]
                sample file : [division by zero]

        updated code and unit test to match sample file content

* Test results

        all unit test pass
        
        all acceptance tests pass except one
                sample2 is looking for a reduced fraction
                this will be implemented in next milestone
        
        useFraction now works correctly
                addition operation previously overwrote addend

## M7 - reduced fractions
### Goals
* Implement function to reduce fraction state to simplest form

* Hook this into central setter function

        If the setter has been properly integrated, no other changes will be needed

### Results
        
* Enabled reduction to simplest form

        implemented in setState
                so logic is applied during all state changes

        uses private helper function based on Euclid's algorithm

* Reverted regex used in operator >>

        added back capture of optional negation signs
        need to concatenate them directly with digits
        atoi operation doesn't like space(s) between sign and digits

* Refactored unit tests in FractionTests.cpp

        case names group together related conditions
        output name simulates a BDD description style

* Add unit test output to git commit

        case and section names provide a good overivew
