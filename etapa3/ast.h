#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>
#include "hash.h"

#define MAX_CHILDREN 4

enum
{
    AST_SYMBOL = 1,
    AST_ADD,
    AST_SUB,
    AST_MULTIPLY,
    AST_DIVIDE,
    AST_LT,
    AST_GT,
    AST_OR,
    AST_AND,
    AST_LE,
    AST_GE,
    AST_EQ,
    AST_DIF,
    AST_NOT,
    AST_DOLLAR,
    AST_HASHTAG,
    AST_PARENTHESIS,
    AST_DECLARATION_LIST,
    AST_FUNCTION_CALL,
    AST_FUNCTION,
    AST_FUNCTION_HEADER,
    AST_FUNCTION_PARAMETERS,
    AST_COMMAND_LIST,
    AST_COMMAND_BLOCK,
    AST_READ,
    AST_PRINT,
    AST_PRINT_LIST,
    AST_RETURN,
    AST_IF,
    AST_IF_ELSE,
    AST_WHILE,
    AST_VARIABLE_NOT_INITIALIZED,
    AST_VARIABLE_INITIALIZED,
    AST_ARRAY_NOT_INITIALIZED,
    AST_ARRAY_INITIALIZED,
    AST_ARRAY_WITH_EXPRESSION,

    AST_ASSIGN_VARIABLE_RIGHT,
    AST_ASSIGN_VARIABLE_LEFT,
    AST_ASSIGN_ARRAY_LEFT,
    AST_ASSIGN_ARRAY_RIGHT,

    AST_LITERAL_LIST,

    AST_PARAMETER_LIST,

    AST_EXPRESSION_LIST
};

typedef struct ast_struct{
  int type;
  HASH_NODE* symbol;
  struct ast_struct* child[MAX_CHILDREN];
} AST;

AST * astCreate(int type, HASH_NODE* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3);
void astPrint(AST* node, int level);

#define astCreateSymbol(x) astCreate(AST_SYMBOL, x, 0, 0, 0, 0)

#endif
