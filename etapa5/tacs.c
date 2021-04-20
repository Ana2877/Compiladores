#include "tacs.h"

TAC *tac_create(TAC_TYPE type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2)
{
    TAC *new_tac = NULL;
    new_tac = (TAC *)malloc(sizeof(TAC));

    new_tac->type = type;
    new_tac->res = res;
    new_tac->op1 = op1;
    new_tac->op2 = op2;

    new_tac->prev = NULL;
    new_tac->next = NULL;

    return new_tac;
}

TAC *tac_join(TAC *tac1, TAC *tac2)
{
    if (!tac1)
        return tac2;
    if (!tac2)
        return tac1;

    TAC *point = tac2;
    while (point->prev)
        point = point->prev;

    point->prev = tac1;

    return tac2;
}

void tac_print(TAC *tac)
{

    if (!tac || tac->type == TAC_SYMBOL)
        return;

    printf("TAC(");
    switch (tac->type)
    {
    case TAC_SYMBOL:
        printf("TAC_SYMBOL");
        break;
    case TAC_TEMP:
        printf("TAC_TEMP");
        break;
    case TAC_LABEL:
        printf("TAC_LABEL");
        break;
    case TAC_COPY_LEFT:
        printf("TAC_COPY_LEFT");
        break;
    case TAC_COPY_RIGHT:
        printf("TAC_COPY_RIGHT");
        break;
    case TAC_COPY_VEC_LEFT:
        printf("TAC_COPY_VEC_LEFT");
        break;
    case TAC_COPY_VEC_RIGHT:
        printf("TAC_COPY_VEC_RIGHT");
        break;
    case TAC_VEC_EXPRESS:
        printf("TAC_VEC_EXPRESS");
        break;
    case TAC_BEGINFUN:
        printf("TAC_BEGINFUN");
        break;
    case TAC_ENDFUN:
        printf("TAC_ENDFUN");
        break;
    case TAC_ADD:
        printf("TAC_ADD");
        break;
    case TAC_SUB:
        printf("TAC_SUB");
        break;
    case TAC_MULTIPLY:
        printf("TAC_MULTIPLY");
        break;
    case TAC_DIVIDE:
        printf("TAC_DIVIDE");
        break;
    case TAC_LT:
        printf("TAC_LT");
        break;
    case TAC_GT:
        printf("TAC_GT");
        break;
    case TAC_OR:
        printf("TAC_OR");
        break;
    case TAC_AND:
        printf("TAC_AND");
        break;
    case TAC_LE:
        printf("TAC_LE");
        break;
    case TAC_GE:
        printf("TAC_GE");
        break;
    case TAC_EQ:
        printf("TAC_EQ");
        break;
    case TAC_DIF:
        printf("TAC_DIF");
        break;
    case TAC_NOT:
        printf("TAC_NOT");
        break;
    case TAC_DOLLAR:
        printf("TAC_DOLLAR");
        break;
    case TAC_HASHTAG:
        printf("TAC_HASHTAG");
        break;
    case TAC_FUNC_CALL:
        printf("TAC_FUNC_CALL");
        break;

    case TAC_READ:
        printf("TAC_READ");
        break;
    case TAC_PRINT:
        printf("TAC_PRINT");
        break;
    case TAC_RETURN:
        printf("TAC_RETURN");
        break;
    case TAC_JUMP:
        printf("TAC_JUMP");
        break;
    case TAC_JUMP_FALSE:
        printf("TAC_JUMP_FALSE");
        break;
    case TAC_UNKNOWN:
    default:
        printf("TAC_UNKNOWN");
        break;
    }

    printf(", %s", tac->res ? tac->res->text : "*");
    printf(", %s", tac->op1 ? tac->op1->text : "*");
    printf(", %s", tac->op2 ? tac->op2->text : "*");
    printf(");\n");
}

void tac_print_recursive(TAC *tac)
{
    if (!tac)
        return;

    tac_print_recursive(tac->prev);
    tac_print(tac);
    fflush(stdout);
}





// ############################# Code generation helpers #############################
TAC* create_function(HASH_NODE* symbol, TAC* code_expr)
{
  return tac_join(tac_join(tac_create(TAC_BEGINFUN, symbol, 0, 0), code_expr), tac_create(TAC_ENDFUN, symbol, 0, 0));
}

TAC* generate_assign_left(HASH_NODE* symbol, TAC* code_expr)
{
  return tac_join(code_expr, tac_create(TAC_COPY_LEFT, symbol, code_expr->res, 0));
}

TAC* generate_assign_right(HASH_NODE* symbol, TAC* code_expr)
{
  return tac_join(code_expr, tac_create(TAC_COPY_RIGHT, code_expr->res, symbol, 0));
}

TAC* generate_boolean_arithmetic_operator(int tac_operation, TAC* code0, TAC* code1)
{
  return  tac_join(tac_join(code0, code1), tac_create(tac_operation, makeTemp(), code0->res, code1->res));
}

TAC* generate_unary_operator(int tac_operation, TAC* code0)
{
  return  tac_join(code0, tac_create(tac_operation, makeTemp(), code0->res, 0));
}

TAC* generate_if(TAC* code0, TAC* code1)
{
  TAC* jmp_tac = 0;
  TAC* label_tac = 0;
  HASH_NODE* new_label = 0;
  new_label = makeLabel();

  jmp_tac = tac_create(TAC_JUMP_FALSE, new_label, code0->res, 0);
  jmp_tac->prev = code0;

  label_tac = tac_create(TAC_LABEL, new_label, 0, 0);
  label_tac->prev = code1;

  return tac_join(jmp_tac, label_tac);

}

TAC* generate_while(TAC* code0, TAC* code1)
{
  TAC* jmp_begin_tac = 0;
  TAC* jmp_false_tac = 0;

  TAC* label_begin_tac = 0;
  TAC* label_end_tac = 0;

  HASH_NODE* beggining_label = 0;
  beggining_label = makeLabel();

  HASH_NODE* end_label = 0;
  end_label = makeLabel();

  label_begin_tac = tac_create(TAC_LABEL, beggining_label, 0, 0);

  jmp_false_tac = tac_create(TAC_JUMP_FALSE, end_label, code0->res, 0);
  jmp_false_tac->prev = code0;

  jmp_begin_tac = tac_create(TAC_JUMP, beggining_label, 0, 0);
  jmp_begin_tac->prev = code1;

  label_end_tac = tac_create(TAC_LABEL, end_label, 0, 0);
  label_end_tac->prev = jmp_begin_tac;

  return tac_join(label_begin_tac, tac_join(jmp_false_tac, label_end_tac));

}

TAC* generate_if_else(TAC* code0, TAC* code1, TAC* code2)
{
  TAC* jmp_false_tac = 0;
  TAC* jmp_end_tac = 0;
  TAC* label_false_tac = 0;
  TAC* label_end_else_tac = 0;

  HASH_NODE* else_label = 0;
  else_label = makeLabel();

  HASH_NODE* end_else_label = 0;
  end_else_label = makeLabel();

  jmp_false_tac = tac_create(TAC_JUMP_FALSE, else_label, code0->res, 0);
  jmp_false_tac->prev = code0;

  jmp_end_tac = tac_create(TAC_JUMP, end_else_label, 0, 0);
  jmp_end_tac->prev = code1;

  label_false_tac = tac_create(TAC_LABEL, else_label, 0, 0);
  label_false_tac->prev = jmp_end_tac;

  label_end_else_tac = tac_create(TAC_LABEL, end_else_label, 0, 0);
  label_end_else_tac->prev = code2;

  return tac_join(jmp_false_tac, tac_join(label_false_tac, label_end_else_tac));

}


TAC* generate_code(AST* node)
{
  if (!node) return 0;

  int i;
  TAC* code[MAX_CHILDREN];

  for (i = 0; i < MAX_CHILDREN; i++)
  {
    code[i] = generate_code(node->child[i]);
  }


  TAC* result;

  switch (node->type)
  {
    case AST_SYMBOL:
      result = tac_create(TAC_SYMBOL, node->symbol, 0, 0);
      break;

    case AST_ADD: result = generate_boolean_arithmetic_operator(TAC_ADD, code[0], code[1]); break;
    case AST_SUB: result = generate_boolean_arithmetic_operator(TAC_SUB, code[0], code[1]); break;
    case AST_DIVIDE: result = generate_boolean_arithmetic_operator(TAC_DIVIDE, code[0], code[1]); break;
    case AST_MULTIPLY: result = generate_boolean_arithmetic_operator(TAC_MULTIPLY, code[0], code[1]); break;
    case AST_GT: result = generate_boolean_arithmetic_operator(TAC_GT, code[0], code[1]); break;
    case AST_LT: result = generate_boolean_arithmetic_operator(TAC_LT, code[0], code[1]); break;
    case AST_OR: result = generate_boolean_arithmetic_operator(TAC_OR, code[0], code[1]); break;
    case AST_AND: result = generate_boolean_arithmetic_operator(TAC_AND, code[0], code[1]); break;
    case AST_DIF: result = generate_boolean_arithmetic_operator(TAC_DIF, code[0], code[1]); break;
    case AST_EQ: result = generate_boolean_arithmetic_operator(TAC_EQ, code[0], code[1]); break;
    case AST_GE: result = generate_boolean_arithmetic_operator(TAC_GE, code[0], code[1]); break;
    case AST_LE: result = generate_boolean_arithmetic_operator(TAC_LE, code[0], code[1]); break;

    case AST_NOT: result = generate_unary_operator(TAC_NOT, code[0]); break;
    case AST_DOLLAR: result = generate_unary_operator(TAC_DOLLAR, code[0]); break;
    case AST_HASHTAG: result = generate_unary_operator(TAC_HASHTAG, code[0]); break;

    case AST_ASSIGN_VARIABLE_RIGHT: result = generate_assign_right(node->child[1]->symbol, code[0]); break;
    case AST_ASSIGN_VARIABLE_LEFT: result = generate_assign_left(node->child[0]->symbol, code[1]); break;

    case AST_ASSIGN_ARRAY_LEFT:
      result = tac_join(tac_join(code[0], code[1]), tac_create(TAC_COPY_VEC_LEFT, code[0]->res, code[1]->res, 0));
      break;
    case AST_ASSIGN_ARRAY_RIGHT:
      result = tac_join(tac_join(code[1], code[0]), tac_create(TAC_COPY_VEC_RIGHT, code[1]->res, code[0]->res, 0));
      break;
    case AST_ARRAY_WITH_EXPRESSION:
      result = tac_create(TAC_VEC_EXPRESS, makeTemp(), node->child[0]->symbol, code[1]->res);
      break;

    case AST_FUNCTION:
      result = create_function(node->child[0]->child[1]->symbol, code[1]);
      break;

    case AST_PRINT:
    case AST_PRINT_LIST:
      result = tac_join(tac_join(code[0], tac_create(TAC_PRINT, code[0]?code[0]->res:0, 0, 0)), code[1]);
      break;

    case AST_RETURN:
      result = tac_join(code[0], tac_create(TAC_RETURN, code[0]?code[0]->res:0, 0, 0));
      break;

    case AST_READ:
      result = tac_create(TAC_READ, code[0]?code[0]->res:0, 0, 0);
      break;

    case AST_IF:
      result = generate_if(code[0], code[1]);
      break;

    case AST_IF_ELSE:
      result = generate_if_else(code[0], code[1], code[2]);
      break;

    case AST_WHILE:
      result = generate_while(code[0], code[1]);
      break;

    case AST_FUNCTION_CALL_NO_PARAMS: ;
      HASH_NODE* func_return_temp = makeTemp();
      result = tac_create(TAC_FUNC_CALL, func_return_temp, code[0]->res, 0);
      break;

    // case AST_FUNCTION_CALL: ;
    //   HASH_NODE* func_return_params_temp = makeTemp();
    //   TAC* tac_func_call = tac_create(TAC_FUNC_CALL, func_return_params_temp, code[0]->res, 0);
    //   result = tac_join(tac_join(tac_join(code[1], tac_create(TAC_FUNC_ARG, code[1]?code[1]->res:0, 0, 0)), code[2]), tac_func_call);
    //   break;
    //
    // case AST_EXPRESSION_LIST: ;
    //   result = tac_join(tac_join(code[0], tac_create(TAC_FUNC_ARG, code[0]?code[0]->res:0, 0, 0)), code[1]);
    //   break;

    default:
      result = tac_join(code[0], tac_join(code[1], tac_join(code[2], code[3])));
      break;
  }

  return result;
}
