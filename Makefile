CXX = clang++
CPPFLAGS = -std=c++17 -O3
OMPFLAGS = -Xpreprocessor -fopenmp -lomp

SRCS := $(wildcard src/*.cpp)

HEADERS := $(wildcard inc/*.hpp)

SRCS_BENCHMARK := $(filter-out src/example.cpp, $(SRCS))

SRCS_EXAMPLE := $(filter-out src/benchmark.cpp, $(SRCS))

OBJS_BENCHMARK := $(patsubst src/%.cpp,%.o,$(SRCS_BENCHMARK))

OBJS_EXAMPLE := $(patsubst src/%.cpp, %.o, $(SRCS_EXAMPLE))

benchmark: $(OBJS_BENCHMARK)
	$(CXX) $^ $(CPPFLAGS) $(OMPFLAGS) -o benchmark

example: $(OBJS_EXAMPLE)
	$(CXX) $^ $(CPPFLAGS) -o example

%.o: src/%.cpp $(HEADERS)
	$(CXX) $< $(CPPFLAGS) -c -o $@

.PHONY: clean

clean:
	rm *.o
