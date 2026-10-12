CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

OBJS = src/main.o src/LanguageModel.o src/TextGenerator.o

slm: $(OBJS)
	$(CXX) $(CXXFLAGS) -o slm $(OBJS)

src/main.o: src/main.cpp src/LanguageModel.h src/TextGenerator.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

src/LanguageModel.o: src/LanguageModel.cpp src/LanguageModel.h
	$(CXX) $(CXXFLAGS) -c src/LanguageModel.cpp -o src/LanguageModel.o

src/TextGenerator.o: src/TextGenerator.cpp src/TextGenerator.h src/LanguageModel.h
	$(CXX) $(CXXFLAGS) -c src/TextGenerator.cpp -o src/TextGenerator.o

clean:
	rm -f slm src/*.o

.PHONY: clean
