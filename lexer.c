#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *KEYWORDS[] = {};

typedef enum {
  TOKEN_IDENTIFIER,
  TOKEN_KEYWORD,
  TOKEN_NUMBER,
  TOKEN_PLUS,
  TOKEN_EOF,
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

void lexer_init(Lexer *lexer, char *input);
void lexer_advance(Lexer *lexer);
void lexer_skip_whitespace(Lexer *lexer);
char *read_word(Lexer *lexer);
char *read_number(Lexer *lexer);
Token lexer_next_token(Lexer *lexer);

void lexer_init(Lexer *lexer, char *input) {
  lexer->source_code = input;
  lexer->position = 0;
  lexer->read_position = 0;
  lexer->current_char = input[0];
}

void lexer_advance(Lexer *lexer) {
  if (lexer->read_position >= strlen(lexer->source_code)) {
    lexer->current_char = '\0';
  } else {
    lexer->current_char = lexer->source_code[lexer->read_position];
  }
  lexer->position = lexer->read_position;
  lexer->read_position++;
}

void lexer_skip_whitespace(Lexer *lexer) {
  while (lexer->current_char == ' ' || lexer->current_char == '\t' ||
         lexer->current_char == '\n' || lexer->current_char == '\r') {
    lexer_advance(lexer);
  }
}

Token lexer_next_token(Lexer *lexer) {
  Token token;
  lexer_skip_whitespace(lexer);

  switch (lexer->current_char) {
  case '\0':
    token.type = TOKEN_EOF;
    token.value = "EOF";
    break;
  case '+':
    token.type = TOKEN_PLUS;
    token.value = "+";
    break;
  default:
    if (isalpha(lexer->current_char)) {
      token.type = TOKEN_IDENTIFIER;
      token.value = read_word(lexer);
    } else if (isdigit(lexer->current_char)) {
      token.type = TOKEN_NUMBER;
      token.value = read_number(lexer);
    }
    break;
  }
  lexer_advance(lexer);
  return token;
}

char *read_word(Lexer *lexer) {
  size_t start_position = lexer->position;
  while (isalpha(lexer->current_char)) {
    lexer_advance(lexer);
  }
  size_t length = lexer->position - start_position;
  char *word = (char *)malloc(length + 1);
  strncpy(word, lexer->source_code + start_position, length);
  word[length] = '\0';
  return word;
}

char *read_number(Lexer *lexer) {
  size_t start_position = lexer->position;
  while (isdigit(lexer->current_char)) {
    lexer_advance(lexer);
  }
  size_t length = lexer->position - start_position;
  char *number = (char *)malloc(length + 1);
  strncpy(number, lexer->source_code + start_position, length);
  number[length] = '\0';
  return number;
}
