#ifndef TOKENTYPE_H
#define TOKENTYPE_H

typedef enum {
  TOKEN_IDENTIFIER,     // 0
  TOKEN_KEYWORD,        // 1
  TOKEN_INVALID,        // 2
  TOKEN_EOF,            // 3
  TOKEN_NUMBER,         // 4
  TOKEN_STRING,         // 5
  TOKEN_PLUS,           // 6
  TOKEN_MULTIPLY,       // 7
  TOKEN_INCREMENT,      // 8 TODO: REMOVE
  TOKEN_DECREMENT,      // 9 TODO: REMOVE
  TOKEN_EXPONENTIATION, // 10
  TOKEN_MINUS,          // 11
  TOKEN_SLASH,          // 12
  TOKEN_EQUALITY,       // 13
  TOKEN_ASSIGNMENT,     // 14
  TOKEN_LT,             // 15
  TOKEN_GT,             // 16
  TOKEN_LTE,            // 17
  TOKEN_GTE,            // 18
  TOKEN_LPAREN,         // 19
  TOKEN_RPAREN,         // 20
  TOKEN_LBRACE,         // 21
  TOKEN_RBRACE,         // 22
  TOKEN_SEMICOLON,      // 23
  TOKEN_COMMA,          // 24
  TOKEN_DOT,            // 25
  TOKEN_LBRACKET,       // 26
  TOKEN_RBRACKET,       // 27
  TOKEN_COMMENT,        // 28
} TokenType;

#endif
