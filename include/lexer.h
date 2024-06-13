#ifndef LEXER_H
#define LEXER_H

#include "../include/structs/Lexer.h"
#include "../include/structs/TokenArray.h"

void lexer_init(Lexer *lexer, char *input);
Token lexer_next_token(Lexer *lexer);
void free_token(Token *token);

void token_array_init(TokenArray *tokenArray);
void token_array_free(TokenArray *tokenArray);
void token_array_add(TokenArray *tokenArray, Token *token);

#endif
