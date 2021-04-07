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
        else
        {
          node->child[0]->child[1]->symbol->type = SYMBOL_VARIABLE;
          node->child[0]->child[1]->symbol->datatype = get_symbol_datatype(node->child[0]->child[0]->symbol->type);
        }
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
        else
        {
          node->child[2]->symbol->type = SYMBOL_VECTOR;
          node->child[2]->symbol->datatype = get_symbol_datatype(node->child[0]->symbol->type);
        }
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
        else
        {
          node->child[1]->symbol->type = SYMBOL_FUNCTION;
          node->child[1]->symbol->datatype = get_symbol_datatype(node->child[0]->symbol->type);
          check_parameters_list(node->child[2]);
        }
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

void check_parameters_list(AST* node)
{
  if(node)
  {
    if((node->child[0]) && (node->child[0]->type == AST_VARIABLE_NOT_INITIALIZED))
    {
      printf("\nVar : %s \n", node->child[0]->child[1]->symbol->text);
      if(node->child[0]->child[1]->symbol->type != SYMBOL_IDENTIFIER)
      {
        printf("Semantic Error: variable %s has already been declared\n", node->child[0]->child[1]->symbol->text);
        ++SemanticErrors;
      }
      node->child[0]->child[1]->symbol->type = SYMBOL_VARIABLE;
      node->child[0]->child[1]->symbol->datatype = get_symbol_datatype(node->child[0]->child[0]->symbol->type);
    }

    if((node->child[1]) && (node->child[1]->type == AST_PARAMETER_LIST))
    {
      check_parameters_list(node->child[1]);
    }
  }
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

void validate_type_AST_DIF(AST* node)
{
  validate_dif_and_equal(node);
}

void validate_type_AST_EQ(AST* node)
{
  validate_dif_and_equal(node);
}

void validate_type_AST_RETURN(AST* node)
{
  DATATYPE operand_type = get_type(node->child[0]);
  if (!is_arithmetic_type(operand_type) && !is_bool_type(operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in RETURN\n");
  }
}

void validate_type_AST_ARRAY_WITH_EXPRESSION(AST* node)
{
  DATATYPE operand_type = get_type(node->child[1]);

  if (!is_arithmetic_type(operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in ARRAY access\n");
  }
}

void validate_type_AST_READ(AST* node)
{
  int operand_type = node->child[0]->symbol->type;
  if (operand_type != SYMBOL_VARIABLE)
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in READ\n");
  }
}

void validate_type_AST_PARENTHESIS(AST* node)
{
  DATATYPE operand_type = get_type(node->child[0]);
  if (is_datatype_error(operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type inside PARENTHESIS\n");
  }
}

void validate_type_AST_DOLLAR(AST* node)
{
  int operand_type = node->child[0]->symbol->type;
  if ((operand_type != SYMBOL_VARIABLE) && (operand_type != SYMBOL_VECTOR))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in the DOLLAR use\n");
  }
}

void validate_type_AST_HASHTAG(AST* node)
{
  int operand_type = node->child[0]->type;
  if (operand_type != SYMBOL_KW_POINTER)
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in the DOLLAR use\n");
  }
}

void validate_type_AST_VARIABLE_INITIALIZED(AST * node)
{
  DATATYPE operand_type = get_type(node->child[0]->child[0]);
  DATATYPE operand_assign_type = get_type(node->child[1]);

  printf("left operand type %d\n", operand_type);
  printf("right operand type %d\n", operand_assign_type);

  if (!(is_arithmetic_type(operand_type) && is_arithmetic_type(operand_assign_type)) && operand_type != operand_assign_type)
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in variable initialized\n");
  }
}

void validate_type_AST_ASSIGN_VARIABLE_RIGHT(AST * node)
{
  DATATYPE expression_type = get_type(node->child[0]);
  DATATYPE operand_assign_type = get_type(node->child[1]);

  if (!(is_arithmetic_type(expression_type) && is_arithmetic_type(operand_assign_type)) && expression_type != operand_assign_type)
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in assign right\n");
  }
}

void validate_type_AST_ASSIGN_VARIABLE_LEFT(AST * node)
{
  DATATYPE expression_type = get_type(node->child[1]);
  DATATYPE operand_assign_type = get_type(node->child[0]);

  printf("left operand type %d\n", expression_type);
  printf("right operand type %d\n", operand_assign_type);

  if (!(is_arithmetic_type(expression_type) && is_arithmetic_type(operand_assign_type)) && expression_type != operand_assign_type)
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in assign left\n");
  }
}

void validate_dif_and_equal(AST* node)
{
  DATATYPE left_operand_type = get_type(node->child[0]);
  DATATYPE right_operand_type = get_type(node->child[1]);

  if (!is_bool_type(left_operand_type) && !is_arithmetic_type(left_operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid left operand type in DIF or EQUAL operation\n");
  }
  else if (!is_bool_type(right_operand_type) && !is_arithmetic_type(right_operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid right operand type in DIF or EQUAL operation\n");
  }
  else if (left_operand_type != right_operand_type)
  {
      SemanticErrors++;
      printf("Semantic Error: The operands type are different in DIF or EQUAL operation\n");
  }
}

void validate_and_or(AST* node)
{
  DATATYPE left_operand_type = get_type(node->child[0]);
  DATATYPE right_operand_type = get_type(node->child[1]);

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
        validate_type_AST_DIF(node);
        break;
    case AST_EQ:
        validate_type_AST_EQ(node);
        break;
    case AST_GE:
        validate_type_AST_GE(node);
        break;
    case AST_LE:
        validate_type_AST_LE(node);
        break;
    case AST_DOLLAR:
        validate_type_AST_DOLLAR(node);
        break;
    case AST_HASHTAG:
        validate_type_AST_HASHTAG(node);
        break;

    case AST_PARENTHESIS:
        validate_type_AST_PARENTHESIS(node);
        break;

    case AST_DECLARATION_LIST:
        break;

    case AST_FUNCTION_CALL:
        //validate_type_AST_FUNCTION_CALL(node);
        break;
    case AST_FUNCTION:
        //validate_type_AST_FUNCTION(node);
        break;
    case AST_FUNCTION_HEADER:
        //validate_type_AST_FUNCTION_HEADER(node);
        break;
    case AST_FUNCTION_PARAMETERS:
        //validate_type_AST_FUNCTION_PARAMETERS(node);
        break;

    case AST_COMMAND_LIST:
        //validate_type_AST_COMMAND_LIST(node);
        break;
    case AST_COMMAND_BLOCK:
        //validate_type_AST_COMMAND_BLOCK(node);
        break;

    case AST_READ:
        validate_type_AST_READ(node);
        break;

    case AST_PRINT:
        //validate_type_AST_PRINT(node);
        break;
    case AST_PRINT_LIST:
        //validate_type_AST_PRINT_LIST(node);
        break;

    case AST_RETURN:
        validate_type_AST_RETURN(node);
        break;

    case AST_IF:
        //validate_type_AST_IF(node);
        break;
    case AST_IF_ELSE:
        //validate_type_AST_IF_ELSE(node);
        break;
    case AST_WHILE:
        //validate_type_AST_WHILE(node);
        break;

    case AST_VARIABLE_NOT_INITIALIZED:
        break;
    case AST_VARIABLE_INITIALIZED:
        validate_type_AST_VARIABLE_INITIALIZED(node);
        break;
    case AST_ARRAY_NOT_INITIALIZED:
        break;
    case AST_ARRAY_INITIALIZED:
        break;
    case AST_ARRAY_WITH_EXPRESSION:
        validate_type_AST_ARRAY_WITH_EXPRESSION(node);
        break;

    case AST_ASSIGN_VARIABLE_RIGHT:
        validate_type_AST_ASSIGN_VARIABLE_RIGHT(node);
        break;
    case AST_ASSIGN_VARIABLE_LEFT:
        validate_type_AST_ASSIGN_VARIABLE_LEFT(node);
        break;
    case AST_ASSIGN_ARRAY_LEFT:
        //validate_type_AST_ASSIGN_ARRAY_LEFT(node);
        break;
    case AST_ASSIGN_ARRAY_RIGHT:
        //validate_type_AST_ASSIGN_ARRAY_RIGHT(node);
        break;

    case AST_LITERAL_LIST:
        //validate_type_AST_LITERAL_LIST(node);
        break;

    case AST_PARAMETER_LIST:
        //validate_type_AST_PARAMETER_LIST(node);
        break;

    case AST_EXPRESSION_LIST:
        //validate_type_AST_EXPRESSION_LIST(node);
        break;
    default:
        break;
  }
  for (i = 0; i < MAX_CHILDREN; i++)
  {
    check_operands(node->child[i]);
  }
}
