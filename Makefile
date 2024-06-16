# compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

# .cpp are the source files and the .o are compiled object files pre-linked
SOURCES = BinarySearchTree.cpp Book.cpp bookdatabase.cpp LibrarySystem.cpp main.cpp security.cpp user_system.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# this is the name of the final executable, so you type ./my_program to run the program
TARGET = my_program

# Default rule, idk but it's necessary
all: $(TARGET)

# Rule to link object files to create the final executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJECTS)

# Phony targets, no idea what this means
.PHONY: all clean