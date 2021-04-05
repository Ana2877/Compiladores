#include "ast.h"

AST * astCreate(int type, HASH_NODE* symbol, AST* child_0, AST* child_1, AST* child_2, AST* child_3)
{
  AST* new_node;

  new_node = (AST*) calloc(1, sizeof(AST));

  new_node->type = type;
  new_node->symbol = symbol;
  new_node->child[0] = child_0;
  new_node->child[1] = child_1;
  new_node->child[2] = child_2;
  new_node->child[3] = child_3;

  return new_node;
}

void astPrint(AST* node, int level)
{
  if (!node)
    return;

  for (int i = 0; i < level; i++)
    printf("  ");

  switch (node->type)
  {
    case AST_SYMBOL: printf("AST_SYMBOL"); break;
    case AST_ADD: printf("AST_ADD"); break;
    case AST_SUB: printf("AST_SUB"); break;
    case AST_MULTIPLY: printf("AST_MULTIPLY"); break;
    case AST_DIVIDE: printf("AST_DIVIDE"); break;
    case AST_LT: printf("AST_LT"); break;
    case AST_GT: printf("AST_GT"); break;
    case AST_OR: printf("AST_OR"); break;
    case AST_AND: printf("AST_AND"); break;
    case AST_LE: printf("AST_LE"); break;
    case AST_GE: printf("AST_GE"); break;
    case AST_EQ: printf("AST_EQ"); break;
    case AST_DIF: printf("AST_DIF"); break;
    case AST_NOT: printf("AST_NOT"); break;
    case AST_DOLLAR: printf("AST_DOLLAR"); break;
    case AST_HASHTAG: printf("AST_HASHTAG"); break;
    case AST_PARENTHESIS: printf("AST_PARENTHESIS"); break;

    case AST_DECLARATION_LIST: printf("AST_DECLARATION_LIST"); break;

    case AST_FUNCTION_CALL: printf("AST_FUNCTION_CALL"); break;
    case AST_FUNCTION: printf("AST_FUNCTION"); break;
    case AST_FUNCTION_HEADER: printf("AST_FUNCTION_HEADER"); break;
    case AST_FUNCTION_PARAMETERS: printf("AST_FUNCTION_PARAMETERS"); break;

    case AST_COMMAND_LIST: printf("AST_COMMAND_LIST"); break;
    case AST_COMMAND_BLOCK: printf("AST_COMMAND_BLOCK"); break;

    case AST_READ: printf("AST_READ"); break;

    case AST_PRINT: printf("AST_PRINT"); break;
    case AST_PRINT_LIST: printf("AST_PRINT_LIST"); break;

    case AST_RETURN: printf("AST_RETURN"); break;

    case AST_IF: printf("AST_IF"); break;
    case AST_IF_ELSE: printf("AST_IF_ELSE"); break;
    case AST_WHILE: printf("AST_WHILE"); break;

    case AST_VARIABLE_NOT_INITIALIZED: printf("AST_VARIABLE_NOT_INITIALIZED"); break;
    case AST_VARIABLE_INITIALIZED: printf("AST_VARIABLE_INITIALIZED"); break;
    case AST_ARRAY_NOT_INITIALIZED: printf("AST_ARRAY_NOT_INITIALIZED"); break;
    case AST_ARRAY_INITIALIZED: printf("AST_ARRAY_INITIALIZED"); break;
    case AST_ARRAY_WITH_EXPRESSION: printf("AST_ARRAY_WITH_EXPRESSION"); break;

    case AST_ASSIGN_VARIABLE_RIGHT: printf("AST_ASSIGN_VARIABLE_RIGHT"); break;
    case AST_ASSIGN_VARIABLE_LEFT: printf("AST_ASSIGN_VARIABLE_LEFT"); break;
    case AST_ASSIGN_ARRAY_LEFT: printf("AST_ASSIGN_ARRAY_LEFT"); break;
    case AST_ASSIGN_ARRAY_RIGHT: printf("AST_ASSIGN_ARRAY_RIGHT"); break;

    case AST_LITERAL_LIST: printf("AST_LITERAL_LIST"); break;

    case AST_PARAMETER_LIST: printf("AST_PARAMETER_LIST"); break;
    case AST_EXPRESSION_LIST: printf("AST_EXPRESSION_LIST"); break;

    default: printf("AST_UNKNOWN"); break;
  }

  printf("\n");

  if (node->symbol)
    fprintf(stderr, "%s\n", node->symbol->text);

  for (int i = 0; i < MAX_CHILDREN; i++)
    astPrint(node->child[i], level + 1);
}
