#include "hash.h"
#include "y.tab.c"

#define SYMBOL_LIT_INTEGER 1
#define SYMBOL_LIT_CHAR 2
#define SYMBOL_LIT_TRUE 3
#define SYMBOL_LIT_FALSE 4
#define SYMBOL_LIT_POINTER 5
#define SYMBOL_LIT_STRING 6
#define SYMBOL_IDENTIFIER 7

int running;
int line_number;

int isRunning(void);
int getLineNumber(void);
