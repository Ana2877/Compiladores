#include "ast.h"
#include "hash.h"
#include "semanticUtils.h"

extern int SemanticErrors;

void check_and_set_declarations(AST* node);
void check_undeclared();
int get_semantic_errors();
int get_symbol_datatype(int type);
void check_operands(AST* node);
void check_parameters_list(AST* node);

void validate_type_AST_SUB(AST* node);
void validate_type_AST_ADD(AST* node);
void validate_type_AST_MULTIPLY(AST* node);
void validate_type_AST_DIVIDE(AST* node);
void validate_type_AST_GT(AST* node);
void validate_type_AST_LT(AST* node);
void validate_type_AST_GE(AST* node);
void validate_type_AST_LE(AST* node);
void validate_arithmetic_and_comparative_expression(AST * node);

void validate_type_AST_OR(AST* node);
void validate_type_AST_AND(AST* node);
void validate_and_or(AST* node);

void validate_type_AST_NOT(AST* node);

void validate_type_AST_EQ(AST* node);
void validate_type_AST_DIF(AST* node);
void validate_dif_and_equal(AST* node);

void validate_type_AST_PARENTHESIS(AST* node);
void validate_type_AST_DOLLAR(AST* node);
void validate_type_AST_HASHTAG(AST* node);
void validate_type_AST_PARENTHESIS(AST* node);
void validate_type_AST_READ(AST* node);
void validate_type_AST_VARIABLE_INITIALIZED(AST * node);
void validate_type_AST_ARRAY_WITH_EXPRESSION(AST* node);

void validate_type_AST_ASSIGN_VARIABLE_RIGHT(AST * node);
void validate_type_AST_ASSIGN_VARIABLE_LEFT(AST * node);
void validate_type_AST_ASSIGN_ARRAY_RIGHT(AST * node);
void validate_type_AST_ASSIGN_ARRAY_LEFT(AST * node);
void validate_assign(AST * node);
