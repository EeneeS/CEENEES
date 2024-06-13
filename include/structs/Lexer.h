#ifndef LEXER_STRUCT_H
#define LEXER_STRUCT_H

#include <stddef.h>

typedef struct {
  char *source_code;
  size_t position;
  size_t read_position;
  char current_char;
  int line;
  int column;
} Lexer;

#endif
