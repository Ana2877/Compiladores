%{
#include "scanner.h"
%}

%%

 /*Reserved Words*/
char																									{return KW_CHAR;}
int																										{return KW_INT;}
bool																									{return KW_BOOL;}
pointer																								{return KW_POINTER;}

if																										{return KW_IF;}
then																									{return KW_THEN;}
else																									{return KW_ELSE;}
while																									{return KW_WHILE;}
read																									{return KW_READ;}
print																									{return KW_PRINT;}
return																								{return KW_RETURN;}

 /*Line Counter*/
"\n"																									{++ line_number;}

 /*Composite Operators*/
(<=)																									{return OPERATOR_LE;}
(>=)																									{return OPERATOR_GE;}
(==)																									{return OPERATOR_EQ;}
(!=)																									{return OPERATOR_DIF;}
(<-)																									{return LEFT_ASSIGN;}
(->)																									{return RIGHT_ASSIGN;}

 /* Literals */
'(.)'																									{return LIT_CHAR;}
\"([^"\\\n]|\\.)*\"      															{return LIT_STRING;}
true  																								{return LIT_TRUE;}
false																									{return LIT_FALSE;}

 /* Integers */
[0-9]+																								{return LIT_INTEGER;}

 /*Special Characters*/
[\-\,\;\:\(\)\[\]\{\}\+\*\/\<\>\|\&\~\$\#] 						{return yytext[0];}

 /*Identifiers*/
[A-Za-z_][A-Za-z0-9_]+ 																{return TK_IDENTIFIER;}

.																											{return TOKEN_ERROR;}

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
