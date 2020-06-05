CXX = clang++
CPPFLAGS = --std=c++17
SRC = ${wildcard *.cpp}

main: ${SRC:%.cpp=%.o}
	${CXX} ${CPPFLAGS} -o main $^

%.o: %.cpp
	${CXX} ${CPPFLAGS} -c $^ -o $@

.PHONY: clean

clean:
	rm *.o

