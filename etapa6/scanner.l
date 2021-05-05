%{
#include "scanner.h"
%}

%x COMMENT

%%
 /*Reserved Words*/
char					{yylval.symbol = hashInsert(yytext, SYMBOL_KW_CHAR); return KW_CHAR;}
int					{yylval.symbol = hashInsert(yytext, SYMBOL_KW_INT); return KW_INT;}
bool					{ yylval.symbol = hashInsert(yytext, SYMBOL_KW_BOOL); return KW_BOOL;}
pointer	      				{  yylval.symbol = hashInsert(yytext, SYMBOL_KW_POINTER);return KW_POINTER;}

if					{return KW_IF;}
then					{return KW_THEN;}
else					{return KW_ELSE;}
while					{return KW_WHILE;}
read                    		{return KW_READ;}
print					{return KW_PRINT;}
return				    	{return KW_RETURN;}

 /*Line Counter*/
"\n"				     	{++ line_number;}

 /*Ignore white spaces and tabs*/
[\t ]

 /* Comments */
"//"(.)*
"/*"					{BEGIN(COMMENT);}

 /*Composite Operators*/
(<=)					{return OPERATOR_LE;}
(>=)					{return OPERATOR_GE;}
(==)					{return OPERATOR_EQ;}
(!=)					{return OPERATOR_DIF;}
(<-)					{return LEFT_ASSIGN;}
(->)					{return RIGHT_ASSIGN;}

 /* Literals */
'(.)'					{yylval.symbol = hashInsert(yytext, SYMBOL_LIT_CHAR); return LIT_CHAR;}
\"([^"\\\n]|\\.)*\"     		{yylval.symbol = hashInsert(yytext, SYMBOL_LIT_STRING); return LIT_STRING;}
true  				    	{ yylval.symbol = hashInsert(yytext, SYMBOL_LIT_TRUE); return LIT_TRUE;}
false					{ yylval.symbol = hashInsert(yytext, SYMBOL_LIT_FALSE);return LIT_FALSE;}

 /* Integers */
[0-9]+				    	{yylval.symbol = hashInsert(yytext, SYMBOL_LIT_INTEGER); return LIT_INTEGER;}

 /*Special Characters*/
[\-\,\;\:\(\)\[\]\{\}\+\*\/\<\>\|\&\~\$\#] 		{return yytext[0];}

 /*Identifiers*/
[A-Za-z_][A-Za-z0-9_]*  		{yylval.symbol = hashInsert(yytext, SYMBOL_IDENTIFIER); return TK_IDENTIFIER;}

 /*Token Error*/
.					{return TOKEN_ERROR;}



<COMMENT>"*/"				{BEGIN(INITIAL);}
<COMMENT>"\n"				{++line_number;}
<COMMENT>.

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
