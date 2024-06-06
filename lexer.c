#include <stdio.h>

const char *KEYWORDS[] = {};

typedef enum {
  TOKEN_IDENTIFIER,
  TOKEN_KEYWORD,
  TOKEN_NUMBER,
  TOKEN_STRING,
  TOKEN_BOOLEAN,
  TOKEN_OPERATOR,
  TOKEN_EOF,
} TokenType;

typedef struct {
  TokenType type;
  char *value;
  int line;
  int column;
} Token;

typedef struct {
  char *source_code;
  size_t position;
  size_t read_position;
  char current_char;
} Lexer;

void lexer_init(Lexer *lexer, char *input) {
  lexer->source_code = input;
  lexer->position = 0;
  lexer->read_position = 0;
  lexer->current_char = input[0];
  printf("%c", lexer->current_char);
}
