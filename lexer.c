#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *KEYWORDS[] = {
    "function", "print", "if", "else", "elseif",
};

// KEEP ORDER, ADD TO END OF LIST !!!
typedef enum {
  TOKEN_IDENTIFIER,     // 0
  TOKEN_KEYWORD,        // 1
  TOKEN_INVALID,        // 2
  TOKEN_EOF,            // 3
  TOKEN_NUMBER,         // 4
  TOKEN_STRING,         // 5
  TOKEN_PLUS,           // 6
  TOKEN_MULTIPLY,       // 7
  TOKEN_INCREMENT,      // 8
  TOKEN_DECREMENT,      // 9
  TOKEN_EXPONENTIATION, // 10
  TOKEN_MINUS,          // 11
  TOKEN_SLASH,          // 12
  TOKEN_EQUALITY,       // 13
  TOKEN_ASSIGNMENT,     // 14
  TOKEN_LTE,            // 15
  TOKEN_GTE,            // 16
  TOKEN_LPAREN,         // 17
  TOKEN_RPAREN,         // 18
  TOKEN_LBRACE,         // 19
  TOKEN_RBRACE,         // 20
  TOKEN_SEMICOLON,      // 21
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
char *read_string(Lexer *lexer);
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
    } else {
      lexer_set_token(&token, TOKEN_PLUS, "+");
    }
    lexer_advance(lexer);
    break;
  case '-':
    if (lexer->source_code[lexer->read_position] == '-') {
      lexer_set_token(&token, TOKEN_DECREMENT, "--");
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_MINUS, "-");
    }
    lexer_advance(lexer);
    break;
  case '*':
    if (lexer->source_code[lexer->read_position] == '*') {
      lexer_set_token(&token, TOKEN_EXPONENTIATION, "**");
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_MULTIPLY, "*");
    }
    lexer_advance(lexer);
    break;
  case '/':
    lexer_set_token(&token, TOKEN_SLASH, "/");
    lexer_advance(lexer);
  case '=':
    if (lexer->source_code[lexer->read_position] == '=') {
      lexer_set_token(&token, TOKEN_EQUALITY, "==");
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_ASSIGNMENT, "=");
    }
    lexer_advance(lexer);
    break;
  case '>':
    if (lexer->source_code[lexer->read_position] == '=') {
      lexer_set_token(&token, TOKEN_GTE, ">=");
      lexer_advance(lexer);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_INVALID, &lexer->current_char);
      lexer_advance(lexer);
    }
    break;
  case '<':
    if (lexer->source_code[lexer->read_position] == '=') {
      lexer_set_token(&token, TOKEN_LTE, "<=");
      lexer_advance(lexer);
      lexer_advance(lexer);
    } else {
      lexer_set_token(&token, TOKEN_INVALID, &lexer->current_char);
      lexer_advance(lexer);
    }
    break;
  case '(':
    lexer_set_token(&token, TOKEN_LPAREN, "(");
    lexer_advance(lexer);
    break;
  case ')':
    lexer_set_token(&token, TOKEN_RPAREN, ")");
    lexer_advance(lexer);
    break;
  case '{':
    lexer_set_token(&token, TOKEN_LBRACE, "{");
    lexer_advance(lexer);
    break;
  case '}':
    lexer_set_token(&token, TOKEN_RBRACE, "}");
    lexer_advance(lexer);
    break;
  case ';':
    lexer_set_token(&token, TOKEN_SEMICOLON, ";");
    lexer_advance(lexer);
    break;
  case '"':
    lexer_set_token(&token, TOKEN_STRING, read_string(lexer));
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
      lexer_set_token(&token, type, word);
    } else if (isdigit(lexer->current_char)) {
      lexer_set_token(&token, TOKEN_NUMBER, read_number(lexer));
    } else {
      lexer_set_token(&token, TOKEN_INVALID, &lexer->current_char);
    }
    break;
  }
  return token;
}

void lexer_set_token(Token *token, TokenType type, char *value) {
  token->type = type;
  token->value = value;
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

void free_token(Token *token) {
  TokenType type = token->type;
  if (type == TOKEN_IDENTIFIER || type == TOKEN_NUMBER ||
      type == TOKEN_STRING) {
    free(token->value);
  }
}
