CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

OBJS = src/main.o src/LanguageModel.o

slm: $(OBJS)
	$(CXX) $(CXXFLAGS) -o slm $(OBJS)

src/main.o: src/main.cpp src/LanguageModel.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

src/LanguageModel.o: src/LanguageModel.cpp src/LanguageModel.h
	$(CXX) $(CXXFLAGS) -c src/LanguageModel.cpp -o src/LanguageModel.o

clean:
	rm -f slm src/*.o

.PHONY: clean
