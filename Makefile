CXX = g++
CXXFLAGS = -g -Wall -O1
CXXSRCS = matmul.cpp matmul-driver.cpp 
BIN = mm

all:
	$(CXX) $(CXXFLAGS) -c $(CXXSRCS)
	$(CXX) $(CXXFLAGS) -o $(BIN) *.o

run :
	./mm > myout
	./compare.py myout output.gold

perf :
	perf stat -e cycles,instructions,branch-misses,cache-misses,cache-references ./mm > myout

compare:
	./compare.py myout output.gold	

clean:
	rm -f *.o
