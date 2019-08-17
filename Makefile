
output: main.o
	g++ main.o -o output

main.o: main.cpp
	g++ -c main.cpp

test: 
	g++ mainTest.cpp -o test

clean:
	rm *.o output
	rm test