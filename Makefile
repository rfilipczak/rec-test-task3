CXX = g++
CXXFLAGS = -std=c++2a -Wpedantic -Wall -Wextra -Wconversion -O3

SRC = ./main.cpp
EXEC = ./task3

all: $(EXEC)


$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)


clean:
	rm -rf $(EXEC)

.PHONY: clean

