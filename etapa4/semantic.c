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
        printf("\nVar : %s ", node->child[0]->child[1]->symbol->text);
        if (node->child[0]->child[1]->symbol->type != SYMBOL_IDENTIFIER)
        {
          printf("Semantic Error: variable %s has already been declared\n", node->child[0]->child[1]->symbol->text);
          ++SemanticErrors;
        }
        node->child[0]->child[1]->symbol->type = SYMBOL_VARIABLE;
      }
      break;

    // case AST_ARRAY_INITIALIZED:
    //   if(node->child[0]->child[2]->symbol){
    //     printf("\nArray Initialized: %s ", node->child[0]->child[2]->symbol->text);
    //     if (node->child[0]->child[2]->symbol->type != SYMBOL_IDENTIFIER)
    //     {
    //       printf("Semantic Error: variable %s has already been declared\n", node->child[0]->child[2]->symbol->text);
    //       ++SemanticErrors;
    //     }
    //     node->child[0]->child[2]->symbol->type = SYMBOL_VECTOR;
    //   }
    //   break;

    case AST_ARRAY_NOT_INITIALIZED:
      if(node->child[2]->symbol){
        printf("\nArray Not Initialized: %s ", node->child[2]->symbol->text);
        if (node->child[2]->symbol->type != SYMBOL_IDENTIFIER)
        {
          printf("Semantic Error: vector %s has already been declared\n", node->child[2]->symbol->text);
          ++SemanticErrors;
        }
        node->child[2]->symbol->type = SYMBOL_VECTOR;
      }
      break;

    case AST_FUNCTION_HEADER:
      if(node->child[1]->symbol){
        printf("\nFunction: %s ", node->child[1]->symbol->text);
        if (node->child[1]->symbol->type != SYMBOL_IDENTIFIER)
        {
            printf("Semantic Error: function %s has already been declared\n", node->child[1]->symbol->text);
            ++SemanticErrors;
        }
        node->child[1]->symbol->type = SYMBOL_FUNCTION;
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

int get_semantic_errors(){
  return SemanticErrors;
}
