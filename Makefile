# Path variables
INCLUDE := include
SOURCE  := src
BIN 	:= bin/exec

# Compiler
CXX = g++

# Non-optional compiler flags like standard, -g, -Wall, -Wextra, -Werror etc.
CXXFLAGS := -std=c++11

# Include path
CPPFLAGS := -I$(INCLUDE)

# Find .cpp files in all subdirectories
SOURCES := $(SOURCE)/*/*.cpp

# Executable
EXEC := game.exe

# Everything depends on the executable
all: $(BIN)/$(EXEC)

# The executable depends on sources
$(BIN)/$(EXEC): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(SOURCES) -o $(BIN)/$(EXEC)

# Run the executable
run: $(BIN)/$(EXEC)
	./$(BIN)/$(EXEC)

# Run with valgrind
valgrind: $(BIN)/$(EXEC)
	valgrind --leak-check=full --show-leak-kinds=all ./$(BIN)/$(EXEC)

# Run executable and compute run time 
time: $(BIN)/$(EXEC)
	time ./$(BIN)/$(EXEC)

# Delete the executable
clean:
	rm -f $(BIN)/$(EXEC)