# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Source files directory
SRCDIR = ./src

# Source files (automatically detect .cpp files in SRCDIR)
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

# Object files (generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Output executable
EXECUTABLE = grepy

# Installation directory
INSTALL_DIR = /usr/local/bin

# Build rule
all: $(EXECUTABLE)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files into the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE)

# Install rule
install: $(EXECUTABLE)
	@echo "Installing $(EXECUTABLE) to $(INSTALL_DIR)"
	sudo cp $(EXECUTABLE) $(INSTALL_DIR)
	@echo "$(EXECUTABLE) installed to $(INSTALL_DIR)"

# Clean rule
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
