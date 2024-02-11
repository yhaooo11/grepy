# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Source files
SOURCES = main.cpp SkipTable.cpp Grepy.cpp

# Object files (generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Output executable
EXECUTABLE = main

# Build rule
all: $(EXECUTABLE)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files into the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

# Clean rule
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
