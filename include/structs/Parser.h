#ifndef PARSER_STRUCT_H
#define PARSER_STRUCT_H

#include <stddef.h>
#include "../structs/TokenArray.h"

typedef struct {
  TokenArray *tokenArray;
  size_t current_token;
} Parser;

#endif
