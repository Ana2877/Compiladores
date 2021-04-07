#include "semanticUtils.h"

DATATYPE get_symbol_datatype(int type)
{
    if (type == SYMBOL_KW_CHAR)
    {
        printf("got char\n");
        return DATATYPE_CHAR;
    }

    if (type == SYMBOL_KW_INT)
    {
        printf("got INT\n");
        return DATATYPE_INT;
    }

    if (type == SYMBOL_KW_POINTER)
    {
        printf("got pointer\n");
        return DATATYPE_POINTER;
    }

    if (type == SYMBOL_KW_BOOL)
    {
        printf("got bool\n");
        return DATATYPE_BOOL;
    }

    return 0;
}

int is_arithmetic_type(int type)
{
  if (type == DATATYPE_CHAR || type == DATATYPE_INT)
    return 1;
  else
    return 0;
}

int is_bool_type(int type)
{
    if (type == DATATYPE_BOOL)
      return 1;
    return 0;
}

int is_datatype_error(int type)
{
    if (type == DATATYPE_ERROR)
      return 1;
    return 0;
}

DATATYPE get_type_AST_SYMBOL(AST* node)
{
  switch (node->symbol->type)
  {
    case SYMBOL_LIT_INTEGER:
      return DATATYPE_INT;

    case SYMBOL_LIT_CHAR:
      return DATATYPE_CHAR;

    case SYMBOL_LIT_TRUE:
    case SYMBOL_LIT_FALSE:
      return DATATYPE_BOOL;

    case SYMBOL_LIT_STRING:
      return DATATYPE_STRING;

    default:
      printf("There is no corresponding datatype to symbol type %d\n", node->symbol->type);
      return DATATYPE_ERROR;
  }
}

DATATYPE get_type_AST_ADD(AST* node)
{
  return get_type_arithmetic(node);
}

DATATYPE get_type_AST_SUB(AST* node)
{
  return get_type_arithmetic(node);
}

DATATYPE get_type_AST_MULTIPLY(AST* node)
{
  return get_type_arithmetic(node);
}

DATATYPE get_type_AST_DIVIDE(AST* node)
{
  return get_type_arithmetic(node);
}

DATATYPE get_type_AST_LE(AST* node)
{
  return get_type_comparator(node);
}

DATATYPE get_type_AST_GE(AST* node)
{
  return get_type_comparator(node);
}

DATATYPE get_type_AST_GT(AST* node)
{
  return get_type_comparator(node);
}

DATATYPE get_type_AST_LT(AST* node)
{
  return get_type_comparator(node);
}

DATATYPE get_type_AST_OR(AST* node)
{
  return get_type_bool(node);
}

DATATYPE get_type_AST_AND(AST* node)
{
  return get_type_bool(node);
}

DATATYPE get_type_AST_DIF(AST* node)
{
  return get_type_dif_or_equal(node);
}

DATATYPE get_type_AST_EQ(AST* node)
{
  return get_type_dif_or_equal(node);
}

DATATYPE get_type_AST_PARENTHESIS(AST* node)
{
  DATATYPE operand_type = get_type(node->child[0]);
  return operand_type;
}

DATATYPE get_type_AST_DOLLAR(AST* node)
{
  return DATATYPE_POINTER;
}

DATATYPE get_type_AST_HASHTAG(AST* node)
{
  DATATYPE operand_type = get_type(node->child[0]);
  return DATATYPE_POINTER;
}

DATATYPE get_type_AST_NOT(AST* node)
{
  DATATYPE operand_type = get_type(node->child[0]);

  if(is_bool_type(operand_type))
    return DATATYPE_BOOL;
  else
    return DATATYPE_ERROR;
}

DATATYPE get_type_bool(AST* node)
{
  DATATYPE left_operand_type = get_type(node->child[0]);
  DATATYPE right_operand_type = get_type(node->child[1]);

  if((is_bool_type(left_operand_type)) && (is_bool_type(right_operand_type)))
    return DATATYPE_BOOL;
  else
    return DATATYPE_ERROR;
}

DATATYPE get_type_arithmetic(AST* node)
{
  DATATYPE left_operand_type = get_type(node->child[0]);
  DATATYPE right_operand_type = get_type(node->child[1]);

  if((is_arithmetic_type(left_operand_type)) && (is_arithmetic_type(right_operand_type)))
    return left_operand_type;
  else
    return DATATYPE_ERROR;
}

DATATYPE get_type_comparator(AST* node)
{
  DATATYPE left_operand_type = get_type(node->child[0]);
  DATATYPE right_operand_type = get_type(node->child[1]);

  if((is_arithmetic_type(left_operand_type)) && (is_arithmetic_type(right_operand_type)))
    return DATATYPE_BOOL;
  else
    return DATATYPE_ERROR;
}

DATATYPE get_type_dif_or_equal(AST* node)
{
  DATATYPE left_operand_type = get_type(node->child[0]);
  DATATYPE right_operand_type = get_type(node->child[1]);

  if((!is_datatype_error(left_operand_type)) && (!is_datatype_error(right_operand_type)))
    return DATATYPE_BOOL;
  else
    return DATATYPE_ERROR;
}

DATATYPE get_type(AST* node)
{
    int i;
    DATATYPE datatype = DATATYPE_ERROR;

    if (node == 0)
      return DATATYPE_ERROR;

    switch (node->type)
    {
      case AST_SYMBOL:
          datatype = get_type_AST_SYMBOL(node);
          break;
      case AST_ADD:
          datatype = get_type_AST_ADD(node);
          break;
      case AST_SUB:
          datatype = get_type_AST_SUB(node);
          break;
      case AST_MULTIPLY:
          datatype = get_type_AST_MULTIPLY(node);
          break;
      case AST_DIVIDE:
          datatype = get_type_AST_DIVIDE(node);
          break;
      case AST_GT:
          datatype = get_type_AST_GT(node);
          break;
      case AST_LT:
          datatype = get_type_AST_LT(node);
          break;
      case AST_OR:
          datatype = get_type_AST_OR(node);
          break;
      case AST_AND:
          datatype = get_type_AST_AND(node);
          break;
      case AST_NOT:
          datatype = get_type_AST_NOT(node);
          break;
      case AST_DIF:
          datatype = get_type_AST_DIF(node);
          break;
      case AST_EQ:
          datatype = get_type_AST_EQ(node);
          break;
      case AST_GE:
          datatype = get_type_AST_GE(node);
          break;
      case AST_LE:
          datatype = get_type_AST_LE(node);
          break;
      case AST_DOLLAR:
          datatype = get_type_AST_DOLLAR(node);
          break;
      case AST_HASHTAG:
          datatype = get_type_AST_HASHTAG(node);
          break;

      case AST_PARENTHESIS:
          datatype = get_type_AST_PARENTHESIS(node);
          break;

      case AST_DECLARATION_LIST:
          //validate_type_AST_DECLARATION_LIST(node);
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
          //validate_type_AST_READ(node);
          break;

      case AST_PRINT:
          //validate_type_AST_PRINT(node);
          break;
      case AST_PRINT_LIST:
          //validate_type_AST_PRINT_LIST(node);
          break;

      case AST_RETURN:
          //validate_type_AST_RETURN(node);
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
          //validate_type_AST_VARIABLE_NOT_INITIALIZED(node);
          break;
      case AST_VARIABLE_INITIALIZED:
          //validate_type_AST_VARIABLE_INITIALIZED(node);
          break;
      case AST_ARRAY_NOT_INITIALIZED:
          //validate_type_AST_ARRAY_NOT_INITIALIZED(node);
          break;
      case AST_ARRAY_INITIALIZED:
          //validate_type_AST_ARRAY_INITIALIZED(node);
          break;
      case AST_ARRAY_WITH_EXPRESSION:
          //validate_type_AST_ARRAY_WITH_EXPRESSION(node);
          break;

      case AST_ASSIGN_VARIABLE_RIGHT:
          //validate_type_AST_ASSIGN_VARIABLE_RIGHT(node);
          break;
      case AST_ASSIGN_VARIABLE_LEFT:
          //validate_type_AST_ASSIGN_VARIABLE_LEFT(node);
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
    return datatype;
}
