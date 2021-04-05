#include "ast.h"

DATATYPE get_symbol_datatype(int type);
int is_arithmetic_type(int type);
DATATYPE get_type(AST* node);

DATATYPE get_type_AST_SYMBOL(AST* node);

DATATYPE get_type_AST_SUB(AST* node);
DATATYPE get_type_AST_ADD(AST* node);
DATATYPE get_type_AST_MULTIPLY(AST* node);
DATATYPE get_type_AST_DIVIDE(AST* node);
DATATYPE get_type_arithmetic(AST* node);

DATATYPE get_type_AST_LE(AST* node);
DATATYPE get_type_AST_GE(AST* node);
DATATYPE get_type_AST_GT(AST* node);
DATATYPE get_type_AST_LT(AST* node);
DATATYPE get_type_comparator(AST* node);
