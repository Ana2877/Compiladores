#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

//lex.yy.h
int yylex();
extern char *yytext;
extern FILE *yyin;


int isRunning(void);
void initMe(void);
int getLineNumber(void);

int main(int argc, char **argv){

	int token;

	initMe();

	if (argc < 2)
    {
    printf("call: ./etapa1 input.txt \n");
    exit(1);
    }
  if (0==(yyin = fopen(argv[1],"r")))
    {
    printf("Cannot open file %s... \n",argv[1]);
    exit(2);
    }

	yyparse();

	hashPrint();
	printf("Acabou\n");

	exit(0); //code for success
}
