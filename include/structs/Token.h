#ifndef TOKEN_H
#define TOKEN_H

#include "../enums/TokenType.h"

typedef struct {
  TokenType type;
  char *value;
  int line;
  int column;
} Token;

#endif
