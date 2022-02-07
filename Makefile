CXX = g++
CXXFLAGS = -std=c++17 -Wpedantic -Wall -Wextra -Wconversion -O3

SRC = ./main.cpp
EXEC = ./task3

all: $(EXEC)


$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)


clean:
	rm -rf $(EXEC)

.PHONY: clean all

