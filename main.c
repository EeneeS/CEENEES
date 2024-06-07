#include "include/file_operations.h"
#include "include/lexer.h"
#include <stdio.h>
#include <stdlib.h>

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
      // printf("Token: Type = %d, Value = %s\n", token.type, token.value);
      token_array_add(&tokenArray, &token);
      free_token(&token);
    } while (token.type != TOKEN_EOF && token.type != TOKEN_INVALID);

    token_array_free(&tokenArray);
    free(source_code);
  }
  return 0;
}

void token_array_free(TokenArray *tokenArray) {
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

