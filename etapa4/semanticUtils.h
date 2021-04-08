#include "ast.h"

int is_arithmetic_type(int type);
int is_bool_type(int type);
int is_datatype_error(int type);
int is_compatible(int type, int type2);

int check_vector_nature(char *text);
int check_function_nature(char *text);
int check_variable_nature(char *text);

void set_is_vector(char *text);
void set_is_function(char *text);

DATATYPE get_symbol_datatype(int type);
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

DATATYPE get_type_AST_OR(AST* node);
DATATYPE get_type_AST_AND(AST* node);
DATATYPE get_type_bool(AST* node);

DATATYPE get_type_AST_NOT(AST* node);

DATATYPE get_type_AST_DIF(AST* node);
DATATYPE get_type_AST_EQ(AST* node);
DATATYPE get_type_dif_or_equal(AST* node);

DATATYPE get_type_AST_PARENTHESIS(AST* node);
DATATYPE get_type_AST_DOLLAR(AST* node);
DATATYPE get_type_AST_RETURN(AST* node);
DATATYPE get_type_AST_VARIABLE_NOT_INITIALIZED(AST* node);
DATATYPE get_type_AST_VARIABLE_INITIALIZED(AST* node);
DATATYPE get_type_AST_ARRAY_WITH_EXPRESSION(AST* node);
DATATYPE get_type_AST_ARRAY_INITIALIZED(AST* node);
DATATYPE get_type_AST_ARRAY_NOT_INITIALIZED(AST* node);
DATATYPE get_type_AST_FUNCTION_CALL_NO_PARAMS(AST* node);
DATATYPE get_type_AST_FUNCTION_CALL(AST* node);
