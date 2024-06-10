#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

typedef struct {
  TokenArray *tokenArray;
  size_t current_token;
} Parser;

void parser_init(Parser *parser, TokenArray *tokenArray);

#endif
