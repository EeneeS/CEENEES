#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

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
  int line;
  int column;
} Lexer;

typedef struct {
  Token *tokens;
  size_t amount;
  size_t capacity;
} TokenArray;

void lexer_init(Lexer *lexer, char *input);
Token lexer_next_token(Lexer *lexer);
void free_token(Token *token);

void token_array_init(TokenArray *tokenArray);
void token_array_free(TokenArray *tokenArray);
void token_array_add(TokenArray *tokenArray, Token *token);

#endif
