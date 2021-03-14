#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>
#include "hash.h"

#define MAX_CHILDREN 4

enum
{
    AST_SYMBOL = 1,
    AST_SYMBOL_VECTOR,
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
    AST_NEGATION,
    AST_FUNC_CALL,
    AST_LPARAMETER,
    AST_LDECL,
    AST_DECLV_NOT_VECTOR,
    AST_DECLV_VECTOR,
    AST_LVECTOR,
    AST_FUNC,
    AST_FUNC_HEADER,
    AST_FUNC_PARAMS,
    AST_LCOMMAND,
    AST_ATTRIB,
    AST_ATTRIB_VEC,
    AST_READ,
    AST_PRINT,
    AST_PRINT_PARAMS,
    AST_RETURN,
    AST_IF,
    AST_IF_ELSE,
    AST_WHILE,
    AST_LOOP
};

typedef struct ast_struct{
  int type;
  HASH_NODE* symbol;
  struct ast_struct* son[MAX_CHILDREN];
} AST;

AST * astCreate(int type, HAS_NODE* symbol, AST* son_0, AST* son_1, AST* son_2, AST* son_3);
void astPrint(AST* node, int level);

#endif
