#include "ast.h"
#include "hash.h"
#include "y.tab.c"

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

int running;
int line_number;

int isRunning(void);
int getLineNumber(void);
