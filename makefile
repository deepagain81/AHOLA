all: myBackoff 

Source:
	g++ -std=c++11 myBackoff.cpp -o myBackoff
	
clean:
	\rm *.o myBackoff 
