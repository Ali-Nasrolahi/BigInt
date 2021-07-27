CC=clang++
CXXFLAGS=-g -Wall -O2

all: BigInt

BigInt: BigInt.o 
	$(CC) $(CXXFLAGS) -o $@ $^

%.o: %.hpp %.cpp 
	$(CC) $(CXXFLAGS) -c $^

clean:
	$(RM) *.o BigInt 