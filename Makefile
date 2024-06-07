# Define the compiler
CC = gcc

# Define the target executable
TARGET = program

# Define the source files
SRC = main.c file_operations.c lexer.c

# Define the object files
OBJ = $(SRC:.c=.o)

# Define the default rule to build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

# Rule to compile the source files into object files
%.o: %.c
	$(CC) -c $< -o $@

# Rule to clean the build
clean:
	rm -f $(TARGET) $(OBJ)

# Rule to run the program
run: $(TARGET)
	./$(TARGET) source_code.txt

.PHONY: clean run

