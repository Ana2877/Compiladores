%{
#include "scanner.h"
%}

%%
char				{return KW_CHAR;}
int					{return KW_INT;}
bool				{return KW_BOOL;}
pointer			{return KW_POINTER;}

if					{return KW_IF;}
then				{return KW_THEN;}
else				{return KW_ELSE;}
while				{return KW_WHILE;}
read				{return KW_READ;}
print				{return KW_PRINT;}
return			{return KW_RETURN;}

"\n"				{++ line_number;}

.		{printf("lixo\n");}

%%

int yywrap(){
	running = 0;
	return 1;
}

int isRunning(void){
	return running;
}

int getLineNumber(void){
	return line_number;
}

void initMe(void){
	running = 1;
	line_number = 1;
}
