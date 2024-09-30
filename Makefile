CXX = g++

# Compiler flags
CXXFLAGS = -Wall -pg -std=c++17 -pthread -fprofile-arcs -ftest-coverage

# Target executable
TARGET = main

# Source files
SRCS = main.cpp reactor.cpp  algorithms.cpp

# Header files
HEADERS = reactor.hpp algorithms.hpp Tree.hpp graph.hpp active_object.hpp leader_follower.hpp pipeline.hpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files, with header dependencies
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS) *.o *.txt *.out gmon.out *.gcno *.gcda *.gcov


.PHONY: all clean