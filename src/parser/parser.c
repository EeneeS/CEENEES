#include "../../include/structs/Parser.h"
#include "../../include/structs/TokenArray.h"

void parser_init(Parser *parser, TokenArray *tokenArray) {
  parser->tokenArray = tokenArray;
  parser->current_token = 0;
}
