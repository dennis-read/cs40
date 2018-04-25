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

        --TBD--

## M3 - operator =
### Goals
* Revise assignment operator

* Direct state changes to common setter function


### Results

        --TBD--

## M4 - operator ++
### Goals
* Revise addition operator

* Direct state changes to common setter function

* Handle fractions with unlike denominators

### Results
        
        --TBD--

## M5 - operator--
### Goals
* Revise subtraction operator

* Direct state changes to common setter function

* Handle fractions with unlike denominators

### Results

        --TBD--

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
        
        --TBD--

## M7 - reduced fractions
### Goals
* Implement function to reduce fraction state to simplest form

* Hook this into central setter function

        If the setter has been properly integrated, no other changes will be needed

### Results
        
        --TBD--