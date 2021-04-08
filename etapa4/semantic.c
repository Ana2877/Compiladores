#include "semantic.h"

int SemanticErrors = 0;

void check_and_set_declarations(AST *node)
{
  int i;
  PARAMETER_TYPE_LIST *parameter_type_list = NULL;
  HASH_NODE *hash_node;

  if (node == 0)
  {
    return;
  }
  switch (node->type)
  {
    case AST_VARIABLE_INITIALIZED:
      if(node->child[0]->child[1]->symbol){
        //printf("\nVar : %s \n", node->child[0]->child[1]->symbol->text);
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
        //printf("\nArray Not Initialized: %s \n", node->child[2]->symbol->text);
        if (node->child[2]->symbol->type != SYMBOL_IDENTIFIER)
        {
          printf("Semantic Error: vector %s has already been declared\n", node->child[2]->symbol->text);
          ++SemanticErrors;
        }
        else
        {
          node->child[2]->symbol->type = SYMBOL_VECTOR;
          node->child[2]->symbol->is_vector = 1;
          node->child[2]->symbol->datatype = get_symbol_datatype(node->child[0]->symbol->type);
        }
      }
      break;

    case AST_FUNCTION_HEADER:
      if(node->child[1]->symbol){
        //printf("\nFunction: %s \n", node->child[1]->symbol->text);
        if (node->child[1]->symbol->type != SYMBOL_IDENTIFIER)
        {
            printf("Semantic Error: function %s has already been declared\n", node->child[1]->symbol->text);
            ++SemanticErrors;
        }
        else
        {
          node->child[1]->symbol->type = SYMBOL_FUNCTION;
          node->child[1]->symbol->is_function = 1;
          node->child[1]->symbol->datatype = get_symbol_datatype(node->child[0]->symbol->type);
          node->child[1]->symbol->parameter_type_list = create_list(0);
          check_parameters_list(node->child[2], node->child[1]->symbol->parameter_type_list);
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

void check_parameters_list(AST* node, PARAMETER_TYPE_LIST *parameter_type_list)
{
  PARAMETER_TYPE_LIST *new_parameter_type_list = NULL;
  if(node)
  {
    if((node->child[0]) && (node->child[0]->type == AST_VARIABLE_NOT_INITIALIZED))
    {
      //printf("\nVar : %s \n", node->child[0]->child[1]->symbol->text);
      if(node->child[0]->child[1]->symbol->type != SYMBOL_IDENTIFIER)
      {
        printf("Semantic Error: variable %s has already been declared\n", node->child[0]->child[1]->symbol->text);
        ++SemanticErrors;
      }
      else
      {
        node->child[0]->child[1]->symbol->type = SYMBOL_VARIABLE;
        node->child[0]->child[1]->symbol->datatype = get_symbol_datatype(node->child[0]->child[0]->symbol->type);
        new_parameter_type_list = create_list(node->child[0]->child[1]->symbol->datatype);
        append_end(parameter_type_list, new_parameter_type_list);
        //print_list(parameter_type_list);
      }
    }

    if((node->child[1]) && (node->child[1]->type == AST_PARAMETER_LIST))
    {
      check_parameters_list(node->child[1], parameter_type_list);
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
  set_is_vector(node->child[0]->symbol->text);
  DATATYPE operand_type = get_type(node->child[1]);

  SemanticErrors += check_vector_nature(node->child[0]->symbol->text);

  if(!is_arithmetic_type(operand_type))
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

DATATYPE find_return_type(AST *node)
{
  DATATYPE operand_type;

  if(node && node->child[0] == 0)
    return 0;

  if(node->child[0]->type == AST_RETURN)
  {
    operand_type = get_type(node->child[0]);
    return operand_type;
  }
  else
  {
    if(node->child[1])
    {
      find_return_type(node->child[1]);
    }
  }
}

void validate_type_AST_FUNCTION(AST* node)
{
  DATATYPE return_type = find_return_type(node->child[1]->child[0]);
  DATATYPE function_type = get_type(node->child[0]->child[0]);

  if(!is_compatible(return_type, function_type))
  {
    SemanticErrors++;
    printf("Semantic Error: the return type differs from the function declaration\n");
  }
}

void check_function_call_parameters(AST* node, PARAMETER_TYPE_LIST *parameter_type_list)
{
  DATATYPE operand_type;
  HASH_NODE *hash_node_param;

  if(node)
  {
    if(parameter_type_list)
    {
      SemanticErrors += check_variable_nature(node->child[0]->symbol->text);

      operand_type = get_type(node->child[0]);
      if(!is_compatible(operand_type, parameter_type_list->datatype))
      {
        SemanticErrors++;
        printf("Semantic Error: invalid argument type in function call\n");
        return;
      }
      else
      {
        check_function_call_parameters(node->child[1], parameter_type_list->next);
      }
    }
    else
    {
      SemanticErrors++;
      printf("Semantic Error: to many arguments in function call\n");
      return;
    }
  }
  else if(parameter_type_list)
  {
    SemanticErrors++;
    printf("Semantic Error: missing arguments in function call\n");
    return;
  }
}

void validate_type_AST_FUNCTION_CALL_NO_PARAMAS(AST* node)
{
  SemanticErrors += check_function_nature(node->child[0]->symbol->text);
}

void validate_type_AST_FUNCTION_CALL(AST* node)
{
  HASH_NODE *hash_node;
  DATATYPE operand_type;
  PARAMETER_TYPE_LIST *parameter_type_list_aux;

  if(check_function_nature(node->child[0]->symbol->text))
  {
    ++SemanticErrors;
  }
  else
  {
    hash_node = hashFind(node->child[0]->symbol->text);
    parameter_type_list_aux = hash_node->parameter_type_list;
    parameter_type_list_aux = parameter_type_list_aux->next;

    if(node->child[1])
    {
      SemanticErrors+= check_variable_nature(node->child[1]->symbol->text);

      operand_type = get_type(node->child[1]);
      if(!is_compatible(operand_type, parameter_type_list_aux->datatype))
      {
        SemanticErrors++;
        printf("Semantic Error: invalid argument type in function call\n");
      }
      check_function_call_parameters(node->child[2], parameter_type_list_aux->next);
    }
  }
}

void validate_type_AST_VARIABLE_INITIALIZED(AST * node)
{
  DATATYPE operand_type = get_type(node->child[0]->child[0]);
  DATATYPE operand_assign_type = get_type(node->child[1]);

  if (!is_compatible(operand_type, operand_assign_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in variable initialized\n");
  }
}

void validate_type_AST_ASSIGN_VARIABLE_RIGHT(AST * node)
{
  validate_assign(node);
}

void validate_type_AST_ASSIGN_VARIABLE_LEFT(AST * node)
{
  validate_assign(node);
}

void validate_type_AST_ASSIGN_ARRAY_RIGHT(AST * node)
{
  validate_assign(node);
}

void validate_type_AST_ASSIGN_ARRAY_LEFT(AST * node)
{
  validate_assign(node);
}

void validate_type_AST_IF(AST * node)
{
  validate_type_if_and_while(node);
}

void validate_type_AST_IF_ELSE(AST * node)
{
  validate_type_if_and_while(node);
}

void validate_type_AST_WHILE(AST * node)
{
  validate_type_if_and_while(node);
}

void validate_type_if_and_while(AST * node)
{
  DATATYPE operand_type = get_type(node->child[0]);

  if (!is_bool_type(operand_type))
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in IF or WHILE\n");
  }
}

void validate_assign(AST * node)
{
  DATATYPE assign_type1 = get_type(node->child[1]);
  DATATYPE assign_type2 = get_type(node->child[0]);

  // printf("left operand type %d\n", assign_type1);
  // printf("right operand type %d\n", assign_type2);

  if (!(is_arithmetic_type(assign_type1) && is_arithmetic_type(assign_type2)) && assign_type1 != assign_type2)
  {
      SemanticErrors++;
      printf("Semantic Error: invalid operand type in assign\n");
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
  else if (!is_compatible(left_operand_type, right_operand_type))
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
        validate_type_AST_FUNCTION_CALL(node);
        break;
    case AST_FUNCTION_CALL_NO_PARAMS:
        validate_type_AST_FUNCTION_CALL_NO_PARAMAS(node);
        break;
    case AST_FUNCTION:
        validate_type_AST_FUNCTION(node);
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
        break;
    case AST_PRINT_LIST:
        break;

    case AST_RETURN:
        validate_type_AST_RETURN(node);
        break;

    case AST_IF:
        validate_type_AST_IF(node);
        break;
    case AST_IF_ELSE:
        validate_type_AST_IF_ELSE(node);
        break;
    case AST_WHILE:
        validate_type_AST_WHILE(node);
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
        validate_type_AST_ASSIGN_ARRAY_LEFT(node);
        break;
    case AST_ASSIGN_ARRAY_RIGHT:
        validate_type_AST_ASSIGN_ARRAY_RIGHT(node);
        break;

    case AST_LITERAL_LIST:
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
