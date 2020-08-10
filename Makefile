CXX = clang++
CPPFLAGS = -std=c++17
OMPFLAGS = -Xpreprocessor -fopenmp -lomp

SRC = ${wildcard *.cpp}

SRC_BENCHMARK := $(filter-out example.cpp, $(SRC))

SRC_EXAMPLE := $(filter-out benchmark.cpp, $(SRC))

benchmark: ${SRC_BENCHMARK:%.cpp=%.o}
	${CXX} ${CPPFLAGS} ${OMPFLAGS} -o benchmark $^

example: ${SRC_EXAMPLE:%.cpp=%.o}
	${CXX} ${CPPFLAGS} -o example $^

%.o: %.cpp
	${CXX} ${CPPFLAGS} -c $^ -o $@

.PHONY: clean

clean:
	rm *.o
