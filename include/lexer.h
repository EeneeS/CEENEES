#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

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
Token lexer_next_token(Lexer *lexer);

#endif
