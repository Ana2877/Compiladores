#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

//lex.yy.h
extern int yylex();
extern char *yytext;
extern FILE *yyin;

void initMe(void);

extern int yyparse();

int main(int argc, char **argv){

	initMe();

	if (argc < 2)
  {
  	fprintf(stderr, "Call: %s input.txt\n", argv[0]);
  	exit(1);
  }
  if (0==(yyin = fopen(argv[1],"r")))
  {
    fprintf(stderr, "Cannot open file %s\n",argv[1]);
    exit(2);
  }

	yyparse();

	hashPrint();
	printf("\n\nSuccesful Compilation!\n\n");

	exit(0); //code for success
}
