# Compiler and linker
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# The source files
SOURCES = main.cpp Customer.cpp Product.cpp Shopping.cpp Storage.cpp utils.cpp

# Object files (replace .cpp with .o)
OBJECTS = $(SOURCES:.cpp=.o)

# The executable
EXEC = my_program

# Default rule: build the executable
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

# Rule to create object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the compiled files
clean:
	rm -f $(OBJECTS) $(EXEC)

# Phony targets (not files)
.PHONY: all clean
