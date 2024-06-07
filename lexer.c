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
  TOKEN_MULTIPLY,
  TOKEN_INCREMENT,
  TOKEN_DECREMENT,
  TOKEN_EXPONENTIATION,
  TOKEN_MINUS,
  TOKEN_SLASH,
  TOKEN_EQUALITY,
  TOKEN_ASSIGNMENT,
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
char *read_operator(Lexer *lexer);
char *read_word(Lexer *lexer);
char *read_number(Lexer *lexer);
Token lexer_next_token(Lexer *lexer);
void lexer_set_token(Token *token, TokenType type, char *value);
void free_token(Token *token);

void lexer_init(Lexer *lexer, char *input) {
  lexer->source_code = input;
  lexer->position = 0;
  lexer->read_position = 1;
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
    if (lexer->source_code[lexer->read_position] == '+') {
      lexer_set_token(&token, TOKEN_INCREMENT, "++");
      lexer_advance(lexer);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_PLUS, "+");
      lexer_advance(lexer);
    }
    break;
  case '-':
    if (lexer->source_code[lexer->read_position] == '-') {
      lexer_set_token(&token, TOKEN_DECREMENT, "--");
      lexer_advance(lexer);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_MINUS, "-");
      lexer_advance(lexer);
    }
    break;
  case '*':
    if (lexer->source_code[lexer->read_position] == '*') {
      lexer_set_token(&token, TOKEN_EXPONENTIATION, "**");
      lexer_advance(lexer);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_MULTIPLY, "*");
      lexer_advance(lexer);
    }
    break;
  case '/':
    lexer_set_token(&token, TOKEN_SLASH, "/");
    lexer_advance(lexer);
  case '=':
    if (lexer->source_code[lexer->read_position] == '=') {
      lexer_set_token(&token, TOKEN_EQUALITY, "==");
      lexer_advance(lexer);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_ASSIGNMENT, "=");
      lexer_advance(lexer);
    }
    break;
  default:
    if (isalpha(lexer->current_char)) {
      lexer_set_token(&token, TOKEN_IDENTIFIER, read_word(lexer));
    } else if (isdigit(lexer->current_char)) {
      lexer_set_token(&token, TOKEN_NUMBER, read_number(lexer));
    }
    break;
  }
  return token;
}

void lexer_set_token(Token *token, TokenType type, char *value) {
  token->type = type;
  token->value = value;
}

// char *read_operator(Lexer *lexer) {
//
//   size_t start_position = lexer->position;
//   size_t length = 1;
//
//   for (int i = 0; i < strlen(operators); i++) {
//     if (lexer->current_char == operators[i]) {
//       length++;
//       lexer_advance(lexer);
//       break;
//     }
//   }
//
//   // TODO: check if a valid operator
//
//   char *operator=(char *) malloc(length + 1);
//   strncpy(operator, lexer->source_code + start_position, length);
//   operator[length] = '\0';
//   return operator;
// }

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

void free_token(Token *token) {
  TokenType type = token->type;
  if (type == TOKEN_IDENTIFIER || type == TOKEN_NUMBER) {
    free(token->value);
  }
}
