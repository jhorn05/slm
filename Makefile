CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

OBJS = src/main.o

slm: $(OBJS)
	$(CXX) $(CXXFLAGS) -o slm $(OBJS)

src/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

clean:
	rm -f slm src/*.o

.PHONY: clean
