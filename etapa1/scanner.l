%{
#include "scanner.h"

%}

%%
int		{printf("KW 'int'\n");}
for		{printf("KW 'for'\n");}
0*		{printf("sequencia de 0's\n");}
[a-zA-Z]+	{printf("identificador %s \n", yytext);}
"+"		{printf("operador mais\n");}
[ \n\t]
.		{printf("lixo\n");}

%%

int yywrap(){
	return 1;
}
