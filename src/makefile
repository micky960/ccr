CC=g++-7 
CXXFLAGS=-std=c++17 -g -O3 -fopenmp
DEPS = def.h
OBJ = main.o def.o cell.o pin.o net.o 

%.o: %.cpp $(DEPS)
	    $(CC) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	    $(CC) $(CXXFLAGS) -o ccr main.o def.o cell.o pin.o net.o -I.

clean:
	    rm -f $(binaries) *.o

