#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
#define SYMBOL_LOCAL_VARIABLE 15
#define SYMBOL_USED_LOCAL_VARIABLE 16

typedef struct hash_node
{
  int type;
  char *text;
  struct hash_node *next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);

#endif
