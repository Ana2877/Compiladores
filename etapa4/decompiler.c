#include "decompiler.h"

void decompile_AST_SYMBOL(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "%s", node->symbol->text);
}

void decompile_AST_DIVIDE(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " / ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_GT(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " > ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_LT(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " < ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_OR(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " | ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_AND(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " & ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_DOLLAR(AST *node, FILE* outputFile)
{
  fprintf(outputFile, " $");
  decompile(node->child[0], outputFile);
}

void decompile_AST_HASHTAG(AST *node, FILE* outputFile)
{
  fprintf(outputFile, " #");
  decompile(node->child[0], outputFile);
}

void decompile_AST_NOT(AST *node, FILE* outputFile)
{
  fprintf(outputFile, " ~");
  decompile(node->child[0], outputFile);
}

void decompile_AST_DIF(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " != ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_EQ(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " == ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_GE(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " >= ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_LE(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " <= ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_PARENTHESIS(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "(");
  decompile(node->child[0], outputFile);
  fprintf(outputFile, ")");
}

// TK_IDENTIFIER '(' expression expression_list ')'
void decompile_AST_FUNCTION_CALL(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, "(");
  decompile(node->child[1], outputFile);
  decompile(node->child[2], outputFile);
  fprintf(outputFile, ")");
}

// '(' parameter parameter_list ')'
void decompile_AST_FUNCTION_PARAMETERS(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  decompile(node->child[1], outputFile);
}

// ',' parameter parameter_list
void decompile_AST_PARAMETER_LIST(AST *node, FILE* outputFile)
{
  fprintf(outputFile, ", ");
  decompile(node->child[0], outputFile);
  decompile(node->child[1], outputFile);
}

// ',' expression expression_list
void decompile_AST_EXPRESSION_LIST(AST *node, FILE* outputFile)
{
  fprintf(outputFile, ", ");
  decompile(node->child[0], outputFile);
  decompile(node->child[1], outputFile);
}

// KW_WHILE '(' expression ')' command
void decompile_AST_WHILE(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "while (");
  decompile(node->child[0], outputFile);
  fprintf(outputFile, ")");
  decompile(node->child[1], outputFile);
}

// KW_PRINT printable_variable print_list
void decompile_AST_PRINT(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "print ");
  decompile(node->child[0], outputFile);
  decompile(node->child[1], outputFile);
}

// printable_variable print_list
void decompile_AST_PRINT_LIST(AST *node, FILE* outputFile)
{
  fprintf(outputFile, ", ");
  decompile(node->child[0], outputFile);
  decompile(node->child[1], outputFile);
}

// KW_RETURN expression
void decompile_AST_RETURN(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "return ");
  decompile(node->child[0], outputFile);
}

void decompile_AST_MULTIPLY(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " * ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_SUB(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " - ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_ADD(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " + ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_ASSIGN_ARRAY_LEFT(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " <- ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_ASSIGN_ARRAY_RIGHT(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " -> ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_ASSIGN_VARIABLE_LEFT(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " <- ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_ASSIGN_VARIABLE_RIGHT(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " -> ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_COMMAND_LIST(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, ";\n  ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_COMMAND_BLOCK(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "{\n");
  decompile(node->child[0], outputFile);
  fprintf(outputFile, "\n}");
}

// ',' assignment assignmentlist
void decompile_AST_PARAMETERS_LIST(AST *node, FILE* outputFile)
{
  fprintf(outputFile, ", ");
  decompile(node->child[0], outputFile);
  decompile(node->child[1], outputFile);
}

//type K_IDENTIFIER function_parameters
void decompile_AST_FUNCTION_HEADER(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " ");
  decompile(node->child[1], outputFile);
  fprintf(outputFile, "(");
  decompile(node->child[2], outputFile);
  fprintf(outputFile, ")");
}

//function command_block
void decompile_AST_FUNCTION(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, "\n");
  decompile(node->child[1], outputFile);
}

//declaration ';' declaration_list
void decompile_AST_DECLARATION_LIST(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, ";\n");
  decompile(node->child[1], outputFile);
}

// KW_READ TK_IDENTIFIER
void decompile_AST_READ(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "read ");
  decompile(node->child[0], outputFile);
}

// KW_IF '(' expression ')' KW_THEN command
void decompile_AST_IF(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "if(");
  decompile(node->child[0], outputFile);
  fprintf(outputFile, ")\n  then \n  ");
  decompile(node->child[1], outputFile);
}

// KW_IF '(' expression ')' KW_THEN command KW_ELSE command
void decompile_AST_IF_ELSE(AST *node, FILE* outputFile)
{
  fprintf(outputFile, "if(");
  decompile(node->child[0], outputFile);
  fprintf(outputFile, ")\n  then \n  ");
  decompile(node->child[1], outputFile);
  fprintf(outputFile, " else \n  ");
  decompile(node->child[2], outputFile);
}

void decompile_AST_VARIABLE_NOT_INITIALIZED(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " ");
  decompile(node->child[1], outputFile);
}

void decompile_AST_VARIABLE_INITIALIZED(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, ": ");
  decompile(node->child[1], outputFile);
}

//type '[' LIT_INTEGER ']' TK_IDENTIFIER
void decompile_AST_ARRAY_NOT_INITIALIZED(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, "[");
  decompile(node->child[1], outputFile);
  fprintf(outputFile, "]");
  decompile(node->child[2], outputFile);
}

//array_not_initialized ':' literal_list
void decompile_AST_ARRAY_INITIALIZED(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, ": ");
  decompile(node->child[1], outputFile);
}

//TK_IDENTIFIER '[' expression ']'
void decompile_AST_ARRAY_WITH_EXPRESSION(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, "[");
  decompile(node->child[1], outputFile);
  fprintf(outputFile, "]");
}

//literal literal_list
void decompile_AST_LITERAL_LIST(AST *node, FILE* outputFile)
{
  decompile(node->child[0], outputFile);
  fprintf(outputFile, " ");
  decompile(node->child[1], outputFile);
}


void decompile(AST* node, FILE *outputFile)
{
    if (!node)
    {
        return;
    }

    switch (node->type)
    {
        case AST_SYMBOL:
            decompile_AST_SYMBOL(node,outputFile);
            break;
        case AST_ADD:
            decompile_AST_ADD(node,outputFile);
            break;
        case AST_SUB:
            decompile_AST_SUB(node,outputFile);
            break;
        case AST_MULTIPLY:
            decompile_AST_MULTIPLY(node,outputFile);
            break;
        case AST_DIVIDE:
            decompile_AST_DIVIDE(node,outputFile);
            break;
        case AST_GT:
            decompile_AST_GT(node,outputFile);
            break;
        case AST_LT:
            decompile_AST_LT(node,outputFile);
            break;
        case AST_OR:
            decompile_AST_OR(node,outputFile);
            break;
        case AST_AND:
            decompile_AST_AND(node,outputFile);
            break;
        case AST_NOT:
            decompile_AST_NOT(node,outputFile);
            break;
        case AST_DIF:
            decompile_AST_DIF(node,outputFile);
            break;
        case AST_EQ:
            decompile_AST_EQ(node,outputFile);
            break;
        case AST_GE:
            decompile_AST_GE(node,outputFile);
            break;
        case AST_LE:
            decompile_AST_LE(node,outputFile);
            break;
        case AST_DOLLAR:
            decompile_AST_DOLLAR(node, outputFile);
            break;
        case AST_HASHTAG:
            decompile_AST_HASHTAG(node, outputFile);
            break;

        case AST_PARENTHESIS:
            decompile_AST_PARENTHESIS(node,outputFile);
            break;

        case AST_DECLARATION_LIST:
            decompile_AST_DECLARATION_LIST(node,outputFile);
            break;

        case AST_FUNCTION_CALL:
            decompile_AST_FUNCTION_CALL(node,outputFile);
            break;
        case AST_FUNCTION:
            decompile_AST_FUNCTION(node,outputFile);
            break;
        case AST_FUNCTION_HEADER:
            decompile_AST_FUNCTION_HEADER(node,outputFile);
            break;
        case AST_FUNCTION_PARAMETERS:
            decompile_AST_FUNCTION_PARAMETERS(node, outputFile);
            break;

        case AST_COMMAND_LIST:
            decompile_AST_COMMAND_LIST(node,outputFile);
            break;
        case AST_COMMAND_BLOCK:
            decompile_AST_COMMAND_BLOCK(node,outputFile);
            break;

        case AST_READ:
            decompile_AST_READ(node,outputFile);
            break;

        case AST_PRINT:
            decompile_AST_PRINT(node,outputFile);
            break;
        case AST_PRINT_LIST:
            decompile_AST_PRINT_LIST(node,outputFile);
            break;

        case AST_RETURN:
            decompile_AST_RETURN(node,outputFile);
            break;

        case AST_IF:
            decompile_AST_IF(node,outputFile);
            break;
        case AST_IF_ELSE:
            decompile_AST_IF_ELSE(node,outputFile);
            break;
        case AST_WHILE:
            decompile_AST_WHILE(node,outputFile);
            break;

        case AST_VARIABLE_NOT_INITIALIZED:
            decompile_AST_VARIABLE_NOT_INITIALIZED(node,outputFile);
            break;
        case AST_VARIABLE_INITIALIZED:
            decompile_AST_VARIABLE_INITIALIZED(node,outputFile);
            break;
        case AST_ARRAY_NOT_INITIALIZED:
            decompile_AST_ARRAY_NOT_INITIALIZED(node,outputFile);
            break;
        case AST_ARRAY_INITIALIZED:
            decompile_AST_ARRAY_INITIALIZED(node,outputFile);
            break;
        case AST_ARRAY_WITH_EXPRESSION:
            decompile_AST_ARRAY_WITH_EXPRESSION(node, outputFile);
            break;

        case AST_ASSIGN_VARIABLE_RIGHT:
            decompile_AST_ASSIGN_VARIABLE_RIGHT(node,outputFile);
            break;
        case AST_ASSIGN_VARIABLE_LEFT:
            decompile_AST_ASSIGN_VARIABLE_LEFT(node,outputFile);
            break;
        case AST_ASSIGN_ARRAY_LEFT:
            decompile_AST_ASSIGN_ARRAY_LEFT(node,outputFile);
            break;
        case AST_ASSIGN_ARRAY_RIGHT:
            decompile_AST_ASSIGN_ARRAY_RIGHT(node,outputFile);
            break;

        case AST_LITERAL_LIST:
            decompile_AST_LITERAL_LIST(node,outputFile);
            break;

        case AST_PARAMETER_LIST:
            decompile_AST_PARAMETER_LIST(node,outputFile);
            break;

        case AST_EXPRESSION_LIST:
            decompile_AST_EXPRESSION_LIST(node,outputFile);
            break;
        default:
            break;
    }
}
