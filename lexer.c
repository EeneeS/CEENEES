#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <wctype.h>

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
  int is_eof;
} Lexer;

void lexer_init(Lexer *lexer, char *input) {
  lexer->source_code = input;
  lexer->position = 0;
  lexer->read_position = 0;
  lexer->current_char = input[0];
  lexer->is_eof = 0;
}

void lexer_advance(Lexer *lexer) {
  if (lexer->read_position >= strlen(lexer->source_code)) {
    lexer->is_eof = 1;
  } else {
    lexer->current_char = lexer->source_code[lexer->read_position];
  }
  lexer->position = lexer->read_position;
  lexer->read_position++;
}

void lexer_skip_whitespace(Lexer *lexer) {
  char current_char = lexer->current_char;
  if (isspace(current_char)) {
    lexer_advance(lexer);
  }
}

Token lexer_next_token(Lexer *lexer) {
  Token token;
  lexer_skip_whitespace(lexer);

  if (lexer->is_eof) {
    token.type = TOKEN_EOF;
    token.value = "EOF";
    return token;
  }

  switch (lexer->current_char) {
  default:
    printf("check other token");
  }

  lexer_advance(lexer);
  return token;
}
