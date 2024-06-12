#include "../include/file_operations.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  char *source_code = read_file(argv[1]);

  if (source_code != NULL) {

    Lexer lexer;
    lexer_init(&lexer, source_code);

    TokenArray tokenArray;
    token_array_init(&tokenArray);

    Token token;

    do {
      token = lexer_next_token(&lexer);
      token_array_add(&tokenArray, &token);
    } while (token.type != TOKEN_EOF && token.type != TOKEN_INVALID);

    if (token.type == TOKEN_INVALID) {
      fprintf(stderr, "Error: Invalid character detected %d:%d\n", token.line,
              token.column);
      token_array_free(&tokenArray);
      free(source_code);
      return 0;
    }

    Parser parser;
    parser_init(&parser, &tokenArray);

    for (size_t i = 0; i < tokenArray.amount; ++i) {
      printf("Token %zu: Line = %d, Column = %d, Type = %d, Value = %s\n", i,
             tokenArray.tokens[i].line, tokenArray.tokens[i].column,
             tokenArray.tokens[i].type, tokenArray.tokens[i].value);
    }

    token_array_free(&tokenArray);
    free(source_code);
  }
  return 0;
}
