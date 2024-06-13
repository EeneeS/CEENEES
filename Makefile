# Define the compiler
CC = gcc

# Define the target executable
TARGET = build/program

# Define the source files
SRC = src/main.c src/file_operations/file_operations.c src/lexer/lexer.c src/parser/parser.c

# Define the object files
OBJ = $(addprefix build/,$(SRC:.c=.o))

# Define the default rule to build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

# Rule to compile the source files into object files
build/%.o: %.c | build
	@mkdir -p $(@D)
	$(CC) -c $< -o $@

# Rule to create the build directory
build:
	mkdir -p $@

# Rule to clean the build
clean:
	rm -rf build

# Rule to run the program
run: $(TARGET)
	./$(TARGET) ./data/source_code.lua

test: $(TARGET)
	./$(TARGET) ./data/test.lua

.PHONY: clean run

