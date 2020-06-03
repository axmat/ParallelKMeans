CXX = clang++
CPP_FLAGS = --std=c++17
SRC = ${wildcard *.cpp}

main: ${SRC:%.cpp=%.o}
	${CXX} -o main $^ ${CPP_FLAGS}

%.o: %.cpp
	${CXX} -c ${CPP_FLAGS} $< -o $@

.PHONY:clean

clean:
	rm *.o

