CXX = clang++
CXXFLAGS = -Wall -O2
OBJ = BigInt.o
DEPS = BigInt.hpp

all: BigInt

BigInt: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS) 
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	$(RM) *.o BigInt 