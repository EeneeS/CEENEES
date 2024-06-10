# Define the compiler
CC = gcc

# Define the target executable
TARGET = build/program

# Define the source files
SRC = main.c file_operations.c lexer.c parser.c

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
	./$(TARGET) ./data/source_code.ce

.PHONY: clean run

