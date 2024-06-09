#include "include/file_operations.h"
#include "include/lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  Token *tokens;
  size_t amount;
  size_t capacity;
} TokenArray;

void token_array_init(TokenArray *tokenArray);
void token_array_free(TokenArray *tokenArray);
void token_array_add(TokenArray *tokenArray, Token *token);

int main(int argc, char *argv[]) {

  if (argc != 2) {
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  char *source_code = read_file(argv[1]);

  if (source_code != NULL) {

    Lexer lexer;
    lexer_init(&lexer, source_code);

    TokenArray tokenArray;
    token_array_init(&tokenArray);

    Token token;

    do {
      token = lexer_next_token(&lexer);
      token_array_add(&tokenArray, &token);
    } while (token.type != TOKEN_EOF && token.type != TOKEN_INVALID);

    for (size_t i = 0; i < tokenArray.amount; ++i) {
      printf("Token %zu: Type = %d, Value = %s\n", i, tokenArray.tokens[i].type,
             tokenArray.tokens[i].value);
    }

    token_array_free(&tokenArray);
    free(source_code);
  }
  return 0;
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
