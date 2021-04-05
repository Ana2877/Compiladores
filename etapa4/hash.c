#include "hash.h"

HASH_NODE *Table[HASH_SIZE];

void hashInit(void){
  int i;
  for(i=0; i<HASH_SIZE; i++)
    Table[i]=0;
}

int hashAddress(char *text){
  int address = 1;
  int i;
  for(i=0; i<strlen(text); i++){
    address = (address * text[i]) % HASH_SIZE + 1;
  }
  return address -1;
}

HASH_NODE *hashFind(char *text){
  HASH_NODE *node;
  int address = hashAddress(text);
  for(node=Table[address]; node; node = node->next){
    if(strcmp(node->text, text) == 0)
      return node;
  }

  return 0;
}

HASH_NODE *hashInsert(char *text, int type){
  HASH_NODE *new_node;
  int address = hashAddress(text);

  if((new_node = hashFind(text)) !=0)
    return new_node;
  new_node = (HASH_NODE *) calloc(1, sizeof(HASH_NODE));
  new_node->type = type;
  new_node->text = (char*) calloc(strlen(text)+1, sizeof(char));
  strcpy(new_node->text, text);
  new_node->next = Table[address];
  Table[address] = new_node;
  return new_node;
}

void hashPrint(void){
  int i;
  HASH_NODE *node;
  for(i=0; i<HASH_SIZE; i++)
    for (node=Table[i]; node; node=node->next)
      printf("Table[%d] has %s with type %d and datatype %d\n", i, node->text, node->type, node->datatype);
}

int hash_check_undeclared(){
  int i, undeclared = 0;
  HASH_NODE *node;
  for(i=0; i<HASH_SIZE; i++)
    for (node=Table[i]; node; node=node->next)
      if (node->type == SYMBOL_IDENTIFIER)
        {
          printf("Semantic error: identifier %s undeclared\n", node->text);
          undeclared++;
        }
  return undeclared;
}
