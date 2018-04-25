

CXXFLAGS=-Wall -g
all: calculator useFraction
calculator: calculator.o Fraction.o
	$(CXX) -o $@ $^

useFraction: useFraction.o Fraction.o
	$(CXX) -o $@ $^

clean:
	rm -f calculator useFraction FractionTests *.o hw1.tar
	rm -f results/*

FractionTests: FractionTests.o Catch.o Fraction.o 
	$(CXX) -o $@ $^

package:
	tar cvf hw1.tar calculator.cpp Fraction.cpp Fraction.h useFraction.cpp Makefile --owner=0 --group=0

test-acceptance: calculator
	./check-samples.sh 

test-unit: FractionTests
	./FractionTests
