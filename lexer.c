#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
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

void lexer_init(Lexer *lexer, char *input);
void lexer_advance(Lexer *lexer);
void lexer_skip_whitespace(Lexer *lexer);
char *read_number(Lexer *lexer);
Token lexer_next_token(Lexer *lexer);

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

  if (isdigit(lexer->current_char)) {
    token.type = TOKEN_NUMBER;
    token.value = read_number(lexer);
    return token;
  }

  lexer_advance(lexer);
  return token;
}

char *read_number(Lexer *lexer) {
  size_t start_position = lexer->position;
  while (isdigit(lexer->current_char)) {
    lexer_advance(lexer);
  }
  size_t length = lexer->position - start_position;
  char *number = (char *)malloc(length + 1);
  strncpy(number, lexer->source_code + start_position, length);
  number[length] = '\0';
  return number;
}
