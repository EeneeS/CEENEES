#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

// KEEP ORDER, ADD TO END OF LIST !!!
typedef enum {
  TOKEN_IDENTIFIER,     // 0
  TOKEN_KEYWORD,        // 1
  TOKEN_INVALID,        // 2
  TOKEN_EOF,            // 3
  TOKEN_NUMBER,         // 4
  TOKEN_STRING,         // 5
  TOKEN_PLUS,           // 6
  TOKEN_MULTIPLY,       // 7
  TOKEN_INCREMENT,      // 8
  TOKEN_DECREMENT,      // 9
  TOKEN_EXPONENTIATION, // 10
  TOKEN_MINUS,          // 11
  TOKEN_SLASH,          // 12
  TOKEN_EQUALITY,       // 13
  TOKEN_ASSIGNMENT,     // 14
  TOKEN_LTE,            // 15
  TOKEN_GTE,            // 16
  TOKEN_LPAREN,         // 17
  TOKEN_RPAREN,         // 18
  TOKEN_LBRACE,         // 19
  TOKEN_RBRACE,         // 20
  TOKEN_SEMICOLON,      // 21
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
