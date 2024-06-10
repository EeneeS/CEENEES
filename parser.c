#include "include/lexer.h"

typedef struct {
  TokenArray *tokenArray;
  size_t current_token;
} Parser;

void parser_init(Parser *parser, TokenArray *tokenArray) {
  parser->tokenArray = tokenArray;
  parser->current_token = 0;
}
