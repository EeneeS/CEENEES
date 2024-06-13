#include "../../include/structs/Lexer.h"
#include "../../include/enums/TokenType.h"
#include "../../include/structs/Token.h"
#include "../../include/structs/TokenArray.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const char *KEYWORDS[] = {
    "and",    "end",  "in",     "repeat", "break", "false", "local",
    "return", "do",   "for",    "nil",    "then",  "else",  "function",
    "not",    "true", "elseif", "if",     "or",    "until", "while"};

void lexer_init(Lexer *lexer, char *input);
void lexer_advance(Lexer *lexer);
void lexer_update_line_column(Lexer *lexer);
void lexer_skip_whitespace(Lexer *lexer);
char *read_operator(Lexer *lexer);
char *read_word(Lexer *lexer);
char *read_number(Lexer *lexer);
char *read_string(Lexer *lexer);
char *read_comment(Lexer *lexer);
Token lexer_next_token(Lexer *lexer);
void lexer_set_token(Token *token, TokenType type, char *value, int line,
                     int number);
void free_token(Token *token);

void token_array_init(TokenArray *tokenArray);
void token_array_free(TokenArray *tokenArray);
void token_array_add(TokenArray *tokenArray, Token *token);

void lexer_init(Lexer *lexer, char *input) {
  lexer->source_code = input;
  lexer->position = 0;
  lexer->read_position = 1;
  lexer->current_char = input[0];
  lexer->line = 1;
  lexer->column = 1;
}

void lexer_advance(Lexer *lexer) {
  lexer_update_line_column(lexer);
  if (lexer->read_position >= strlen(lexer->source_code)) {
    lexer->current_char = '\0';
  } else {
    lexer->current_char = lexer->source_code[lexer->read_position];
  }
  lexer->position = lexer->read_position;
  lexer->read_position++;
}

void lexer_update_line_column(Lexer *lexer) {
  if (lexer->current_char == '\n') {
    lexer->line++;
    lexer->column = 1;
  } else if (lexer->current_char == '\t') {
    lexer->column += 4; // Assume a tab is 4 spaces
  } else {
    lexer->column++;
  }
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

  int line = lexer->line;
  int column = lexer->column;

  switch (lexer->current_char) {
  case '\0':
    lexer_set_token(&token, TOKEN_EOF, "EOF", line, column);
    break;
  case '+':
    lexer_set_token(&token, TOKEN_PLUS, "+", line, column);
    lexer_advance(lexer);
    break;
  case '-':
    if (lexer->source_code[lexer->read_position] == '-') {
      lexer_set_token(&token, TOKEN_COMMENT, read_comment(lexer), line, column);
    } else {
      lexer_set_token(&token, TOKEN_MINUS, "-", line, column);
      lexer_advance(lexer);
    }
    break;
  case '*':
    lexer_set_token(&token, TOKEN_MULTIPLY, "*", line, column);
    lexer_advance(lexer);
    break;
  case '/':
    lexer_set_token(&token, TOKEN_SLASH, "/", line, column);
    lexer_advance(lexer);
    break;
  case '^':
    lexer_set_token(&token, TOKEN_EXPONENTIATION, "^", line, column);
    lexer_advance(lexer);
  case '=':
    if (lexer->source_code[lexer->read_position] == '=') {
      lexer_set_token(&token, TOKEN_EQUALITY, "==", line, column);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_ASSIGNMENT, "=", line, column);
    }
    lexer_advance(lexer);
    break;
  case '>':
    if (lexer->source_code[lexer->read_position] == '=') {
      lexer_set_token(&token, TOKEN_GTE, ">=", line, column);
      lexer_advance(lexer);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_GT, ">", line, column);
      lexer_advance(lexer);
    }
    break;
  case '<':
    if (lexer->source_code[lexer->read_position] == '=') {
      lexer_set_token(&token, TOKEN_LTE, "<=", line, column);
      lexer_advance(lexer);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_LT, "<", line, column);
      lexer_advance(lexer);
    }
    break;
  case '(':
    lexer_set_token(&token, TOKEN_LPAREN, "(", line, column);
    lexer_advance(lexer);
    break;
  case ')':
    lexer_set_token(&token, TOKEN_RPAREN, ")", line, column);
    lexer_advance(lexer);
    break;
  case '[':
    lexer_set_token(&token, TOKEN_LBRACKET, "[", line, column);
    lexer_advance(lexer);
    break;
  case ']':
    lexer_set_token(&token, TOKEN_RBRACKET, "]", line, column);
    lexer_advance(lexer);
    break;
  case '{':
    lexer_set_token(&token, TOKEN_LBRACE, "{", line, column);
    lexer_advance(lexer);
    break;
  case '}':
    lexer_set_token(&token, TOKEN_RBRACE, "}", line, column);
    lexer_advance(lexer);
    break;
  case ';':
    lexer_set_token(&token, TOKEN_SEMICOLON, ";", line, column);
    lexer_advance(lexer);
    break;
  case '.':
    lexer_set_token(&token, TOKEN_DOT, ".", line, column);
    lexer_advance(lexer);
    break;
  case ',':
    lexer_set_token(&token, TOKEN_COMMA, ",", line, column);
    lexer_advance(lexer);
    break;
  case '"':
    lexer_set_token(&token, TOKEN_STRING, read_string(lexer), line, column);
    break;
  default:
    if (isalpha(lexer->current_char)) {
      char *word = read_word(lexer);
      TokenType type = TOKEN_IDENTIFIER;
      for (size_t i = 0; i < sizeof(KEYWORDS) / sizeof(KEYWORDS[0]); i++) {
        if (strcmp(word, KEYWORDS[i]) == 0) {
          type = TOKEN_KEYWORD;
          break;
        }
      }
      lexer_set_token(&token, type, word, line, column);
    } else if (isdigit(lexer->current_char)) {
      lexer_set_token(&token, TOKEN_NUMBER, read_number(lexer), line, column);
    } else {
      lexer_set_token(&token, TOKEN_INVALID, &lexer->current_char, line,
                      column);
    }
    break;
  }
  return token;
}

void lexer_set_token(Token *token, TokenType type, char *value, int line,
                     int column) {
  token->type = type;
  token->value = value;
  token->line = line;
  token->column = column;
}

char *read_string(Lexer *lexer) {
  size_t start_position = lexer->position;
  lexer_advance(lexer);
  while (lexer->current_char != '"') {
    lexer_advance(lexer);
  }
  lexer_advance(lexer);
  size_t length = lexer->position - start_position;
  char *string = (char *)malloc(length + 1);
  strncpy(string, lexer->source_code + start_position, length);
  string[length] = '\0';
  return string;
}

char *read_word(Lexer *lexer) {
  size_t start_position = lexer->position;
  while (isalpha(lexer->current_char) || lexer->current_char == '_') {
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

char *read_comment(Lexer *lexer) {
  lexer_advance(lexer);
  lexer_advance(lexer);
  size_t start_position = lexer->position;
  while (lexer->current_char != '\n') {
    lexer_advance(lexer);
  }
  size_t length = lexer->position - start_position;
  char *comment = (char *)malloc(length + 1);
  strncpy(comment, lexer->source_code + start_position, length);
  comment[length] = '\0';
  return comment;
}

void free_token(Token *token) {
  TokenType type = token->type;
  if (type == TOKEN_IDENTIFIER || type == TOKEN_NUMBER ||
      type == TOKEN_STRING || type == TOKEN_COMMENT) {
    free(token->value);
  }
}

void token_array_free(TokenArray *tokenArray) {
  for (size_t i = 0; i < tokenArray->amount; i++) {
    free_token(&tokenArray->tokens[i]);
  }
  free(tokenArray->tokens);
  tokenArray->tokens = NULL;
  tokenArray->amount = tokenArray->capacity = 0;
}

void token_array_init(TokenArray *tokenArray) {
  tokenArray->tokens = malloc(1 * sizeof(Token));
  if (tokenArray->tokens == NULL) {
    return;
  }
  tokenArray->amount = 0;
  tokenArray->capacity = 1;
}

void token_array_add(TokenArray *tokenArray, Token *token) {
  if (tokenArray->amount >= tokenArray->capacity) {
    Token *ptr =
        realloc(tokenArray->tokens, (tokenArray->capacity + 1) * sizeof(Token));
    if (ptr == NULL) {
      return;
    }
    tokenArray->tokens = ptr;
    tokenArray->capacity++;
  }
  tokenArray->tokens[tokenArray->amount] = *token;
  tokenArray->amount++;
}
