#include "include/file_operations.h"
#include "include/lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  char *source_code = read_file(argv[1]);

  if (source_code != NULL) {

    Lexer lexer;
    lexer_init(&lexer, source_code);

    Token token;

    do {
      token = lexer_next_token(&lexer);
      printf("Token: Type = %d, Value = %s\n", token.type, token.value);
    } while (token.type != TOKEN_EOF);

    free(source_code);
  }
  return 0;
}
