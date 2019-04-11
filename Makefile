CXX = g++
CXXFLAGS = -std=c++11 -Wall
prog: frac.o main.o
	$(CXX) -o $@ $^ $(CXXFLAGS)
frac.o: frac.h
main.o: frac.h
clean:
	rm -rf *.o *~
