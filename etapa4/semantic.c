#include "semantic.h"

int SemanticErrors = 0;

void check_and_set_declarations(AST *node)
{
  int i;
  if (node == 0)
  {
    return;
  }
  switch (node->type)
  {
    case AST_VARIABLE_INITIALIZED:
      if(node->child[0]->child[1]->symbol){
        printf("\nVar : %s \n", node->child[0]->child[1]->symbol->text);
        if (node->child[0]->child[1]->symbol->type != SYMBOL_IDENTIFIER)
        {
          printf("Semantic Error: variable %s has already been declared\n", node->child[0]->child[1]->symbol->text);
          ++SemanticErrors;
        }
        node->child[0]->child[1]->symbol->type = SYMBOL_VARIABLE;
        node->child[0]->child[1]->symbol->datatype = get_symbol_datatype(node->child[0]->child[0]->symbol->type);
      }
      break;

    case AST_ARRAY_NOT_INITIALIZED:
      if(node->child[2]->symbol){
        printf("\nArray Not Initialized: %s \n", node->child[2]->symbol->text);
        if (node->child[2]->symbol->type != SYMBOL_IDENTIFIER)
        {
          printf("Semantic Error: vector %s has already been declared\n", node->child[2]->symbol->text);
          ++SemanticErrors;
        }
        node->child[2]->symbol->type = SYMBOL_VECTOR;
        node->child[2]->symbol->datatype = get_symbol_datatype(node->child[0]->symbol->type);
      }
      break;

    case AST_FUNCTION_HEADER:
      if(node->child[1]->symbol){
        printf("\nFunction: %s \n", node->child[1]->symbol->text);
        if (node->child[1]->symbol->type != SYMBOL_IDENTIFIER)
        {
            printf("Semantic Error: function %s has already been declared\n", node->child[1]->symbol->text);
            ++SemanticErrors;
        }
        node->child[1]->symbol->type = SYMBOL_FUNCTION;
        node->child[1]->symbol->datatype = get_symbol_datatype(node->child[0]->symbol->type);
      }
      break;
    default: break;
  }

  for (int i = 0; i < MAX_CHILDREN; i++)
    check_and_set_declarations(node->child[i]);
}

void check_undeclared()
{
    SemanticErrors += hash_check_undeclared();
}

int get_semantic_errors()
{
  return SemanticErrors;
}


void validate_type_AST_ADD(AST* node)
{
  validate_arithmetic_and_comparative_expression(node);
}

void validate_type_AST_SUB(AST* node)
{
  validate_arithmetic_and_comparative_expression(node);
}

void validate_type_AST_MULTIPLY(AST* node)
{
  validate_arithmetic_and_comparative_expression(node);
}

void validate_type_AST_DIVIDE(AST* node)
{
  validate_arithmetic_and_comparative_expression(node);
}

void validate_type_AST_GT(AST* node)
{
  validate_arithmetic_and_comparative_expression(node);
}

void validate_type_AST_LT(AST* node)
{
  validate_arithmetic_and_comparative_expression(node);
}

void validate_type_AST_GE(AST* node)
{
  validate_arithmetic_and_comparative_expression(node);
}

void validate_type_AST_LE(AST* node)
{
  validate_arithmetic_and_comparative_expression(node);
}

void validate_type_AST_OR(AST* node)
{
  validate_and_or(node);
}

void validate_type_AST_AND(AST* node)
{
  validate_and_or(node);
}

void validate_type_AST_NOT(AST* node)
{
  DATATYPE operand_type = get_type(node->child[0]);

  printf("operand type %d\n", operand_type);

  if (!is_bool_type(operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in NOT\n");
  }
}

void validate_and_or(AST* node)
{
  DATATYPE left_operand_type = get_type(node->child[0]);
  DATATYPE right_operand_type = get_type(node->child[1]);

  printf("left operand type %d\n", left_operand_type);
  printf("right operand type %d\n", right_operand_type);

  if (!is_bool_type(left_operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid left operand type in AND or OR operation\n");
  }
  else if (!is_bool_type(right_operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid right operand type in AND or OR operation\n");
  }
}

void validate_arithmetic_and_comparative_expression(AST * node)
{
  DATATYPE left_operand_type = get_type(node->child[0]);
  DATATYPE right_operand_type = get_type(node->child[1]);

  // printf("left operand type %d\n", left_operand_type);
  // printf("right operand type %d\n", right_operand_type);

  if (!is_arithmetic_type(left_operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid left operand type in Arithmetic expression\n");
  }
  else if (!is_arithmetic_type(right_operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid right operand type in Arithmetic expression\n");
  }
}

void check_operands(AST* node)
{
  int i;

  if (node == 0)
    return;

  switch (node->type)
  {
    case AST_SYMBOL:
        break;
    case AST_ADD:
        validate_type_AST_ADD(node);
        break;
    case AST_SUB:
        validate_type_AST_SUB(node);
        break;
    case AST_MULTIPLY:
        validate_type_AST_MULTIPLY(node);
        break;
    case AST_DIVIDE:
        validate_type_AST_DIVIDE(node);
        break;
    case AST_GT:
        validate_type_AST_GT(node);
        break;
    case AST_LT:
        validate_type_AST_LT(node);
        break;
    case AST_OR:
        validate_type_AST_OR(node);
        break;
    case AST_AND:
        validate_type_AST_AND(node);
        break;
    case AST_NOT:
        validate_type_AST_NOT(node);
        break;
    case AST_DIF:
        //validate_type_AST_DIF(node);
        break;
    case AST_EQ:
        //validate_type_AST_EQ(node);
        break;
    case AST_GE:
        validate_type_AST_GE(node);
        break;
    case AST_LE:
        validate_type_AST_LE(node);
        break;
    case AST_DOLLAR:
        //validate_type_AST_DOLLAR(node, outputFile);
        break;
    case AST_HASHTAG:
        //validate_type_AST_HASHTAG(node, outputFile);
        break;

    case AST_PARENTHESIS:
        //validate_type_AST_PARENTHESIS(node);
        break;

    case AST_DECLARATION_LIST:
        //validate_type_AST_DECLARATION_LIST(node);
        break;

    case AST_FUNCTION_CALL:
        //validate_type_AST_FUNCTION_CALL(node,outputFile);
        break;
    case AST_FUNCTION:
        //validate_type_AST_FUNCTION(node,outputFile);
        break;
    case AST_FUNCTION_HEADER:
        //validate_type_AST_FUNCTION_HEADER(node,outputFile);
        break;
    case AST_FUNCTION_PARAMETERS:
        //validate_type_AST_FUNCTION_PARAMETERS(node, outputFile);
        break;

    case AST_COMMAND_LIST:
        //validate_type_AST_COMMAND_LIST(node,outputFile);
        break;
    case AST_COMMAND_BLOCK:
        //validate_type_AST_COMMAND_BLOCK(node,outputFile);
        break;

    case AST_READ:
        //validate_type_AST_READ(node,outputFile);
        break;

    case AST_PRINT:
        //validate_type_AST_PRINT(node,outputFile);
        break;
    case AST_PRINT_LIST:
        //validate_type_AST_PRINT_LIST(node,outputFile);
        break;

    case AST_RETURN:
        //validate_type_AST_RETURN(node,outputFile);
        break;

    case AST_IF:
        //validate_type_AST_IF(node,outputFile);
        break;
    case AST_IF_ELSE:
        //validate_type_AST_IF_ELSE(node,outputFile);
        break;
    case AST_WHILE:
        //validate_type_AST_WHILE(node,outputFile);
        break;

    case AST_VARIABLE_NOT_INITIALIZED:
        //validate_type_AST_VARIABLE_NOT_INITIALIZED(node,outputFile);
        break;
    case AST_VARIABLE_INITIALIZED:
        //validate_type_AST_VARIABLE_INITIALIZED(node,outputFile);
        break;
    case AST_ARRAY_NOT_INITIALIZED:
        //validate_type_AST_ARRAY_NOT_INITIALIZED(node,outputFile);
        break;
    case AST_ARRAY_INITIALIZED:
        //validate_type_AST_ARRAY_INITIALIZED(node,outputFile);
        break;
    case AST_ARRAY_WITH_EXPRESSION:
        //validate_type_AST_ARRAY_WITH_EXPRESSION(node, outputFile);
        break;

    case AST_ASSIGN_VARIABLE_RIGHT:
        //validate_type_AST_ASSIGN_VARIABLE_RIGHT(node,outputFile);
        break;
    case AST_ASSIGN_VARIABLE_LEFT:
        //validate_type_AST_ASSIGN_VARIABLE_LEFT(node,outputFile);
        break;
    case AST_ASSIGN_ARRAY_LEFT:
        //validate_type_AST_ASSIGN_ARRAY_LEFT(node,outputFile);
        break;
    case AST_ASSIGN_ARRAY_RIGHT:
        //validate_type_AST_ASSIGN_ARRAY_RIGHT(node,outputFile);
        break;

    case AST_LITERAL_LIST:
        //validate_type_AST_LITERAL_LIST(node,outputFile);
        break;

    case AST_PARAMETER_LIST:
        //validate_type_AST_PARAMETER_LIST(node,outputFile);
        break;

    case AST_EXPRESSION_LIST:
        //validate_type_AST_EXPRESSION_LIST(node,outputFile);
        break;
    default:
        break;
  }
  for (i = 0; i < MAX_CHILDREN; i++)
  {
      //if (node->type == AST_FUNC_PARAMS_DEC)
      //{
      //    return;
      //}

      check_operands(node->child[i]);
  }
}
