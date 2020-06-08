CXX = clang++
CPPFLAGS = -std=c++17
OMPFLAGS = -Xpreprocessor -fopenmp -lomp
SRC = ${wildcard *.cpp}

main: ${SRC:%.cpp=%.o}
	${CXX} ${CPPFLAGS} -o main $^

%.o: %.cpp
	${CXX} ${CPPFLAGS} ${OMPFLAGS} -c $^ -o $@

.PHONY: clean

clean:
	rm *.o

