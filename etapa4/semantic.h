#include "ast.h"
#include "hash.h"
#include "semanticUtils.h"

extern int SemanticErrors;

void check_and_set_declarations(AST* node);
void check_undeclared();
int get_semantic_errors();
int get_symbol_datatype(int type);
void check_operands(AST* node);

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
