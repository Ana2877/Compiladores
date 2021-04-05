#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "decompiler.h"
#include "semantic.h"

//lex.yy.h
extern int yylex();
extern char *yytext;
extern FILE *yyin;
extern AST *Root;

void initMe(void);

extern int yyparse();

int main(int argc, char **argv){

	int semantic_errors = 0;

	initMe();

	if (argc < 3)
  {
  	fprintf(stderr, "Call: %s input.txt\n", argv[0]);
  	exit(1);
  }
  if (0==(yyin = fopen(argv[1],"r")))
  {
    fprintf(stderr, "Cannot open file %s\n",argv[1]);
    exit(2);
  }

	FILE *file =fopen(argv[2], "w");
	if (file == 0) {
		fprintf(stderr, "Cannot open file %s\n", argv[2]);
		exit(2);
	}

	yyparse();
	printf("\n");

	semantic_errors = get_semantic_errors();

	hashPrint();

	decompile(Root, file);

	if (semantic_errors > 0)
	{
		printf("Compilation ERROR! There was %d semantic errors \n", semantic_errors);
		exit(4);
	}

	printf("\n\nSuccesful Compilation!\n\n");

	exit(0); //code for success
}
