#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parameter_type_list.h"

#define HASH_SIZE 997

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_CHAR 2
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_KW_BOOL 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7
#define SYMBOL_KW_INT 8
#define SYMBOL_KW_POINTER 9
#define SYMBOL_KW_CHAR 10

#define SYMBOL_VARIABLE 12
#define SYMBOL_VECTOR 13
#define SYMBOL_FUNCTION 14

typedef enum
{
  DATATYPE_ERROR = -1,
  DATATYPE_UNDEFINED = 0,
  DATATYPE_CHAR = 1,
  DATATYPE_INT,
  DATATYPE_POINTER,
  DATATYPE_BOOL,
  DATATYPE_STRING,
} DATATYPE;

typedef struct hash_node
{
  DATATYPE datatype;
  int type;
  char *text;
  struct hash_node *next;
  PARAMETER_TYPE_LIST *parameter_type_list;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
int hash_check_undeclared();

#endif
