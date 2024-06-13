#ifndef TOKEN_H
#define TOKEN_H

typedef struct {
  TokenType type;
  char *value;
  int line;
  int column;
} Token;

#endif
