#include <stdio.h>
#include <stdlib.h>

typedef enum {
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_OPERATOR,
  TOKEN_KEYWORD,
  TOKEN_EOF,
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

char *read_file();

int main() {

  char *source_code = read_file();

  if (source_code != NULL) {
    printf("%s", source_code);
    free(source_code);
  }

  return 0;
}

char *read_file() {

  FILE *fptr;
  char *source_code;
  long file_size;

  fptr = fopen("source_code.ce", "r");

  if (fptr == NULL) {
    perror("Error opening file.");
    return NULL;
  }

  fseek(fptr, 0, SEEK_END);
  file_size = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);

  source_code = malloc(file_size + 1);
  if (source_code == NULL) {
    perror("Error allocation memory");
    fclose(fptr);
    return NULL;
  }

  fread(source_code, 1, file_size, fptr);
  source_code[file_size] = '\0';
  fclose(fptr);
  return source_code;
}
