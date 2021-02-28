%token KW_CHAR
%token KW_INT
%token KW_BOOL
%token KW_POINTER

%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token LEFT_ASSIGN
%token RIGHT_ASSIGN
%token TK_IDENTIFIER

%token LIT_INTEGER
%token LIT_TRUE
%token LIT_FALSE
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%%
programa: declaration_list;

declaration_list: init_declaration end_declaration | ;

end_declaration: ';' init_declaration end_declaration |;

/*init_declaration: variable | KW_INT TK_IDENTIFIER | KW_INT TK_IDENTIFIER '(' ')' function_body;*/
init_declaration: variable | array;

/* Variable declaration */
variable: type TK_IDENTIFIER ':' literal;

/* Array declaration */
array: array_initialized | array_not_initialized;

array_not_initialized: type '[' LIT_INTEGER ']' TK_IDENTIFIER

array_initialized: array_not_initialized ':'



/* types */
type: KW_CHAR | KW_INT | KW_BOOL | KW_POINTER;

/* literals, except string */
literal: LIT_INTEGER | LIT_TRUE | LIT_FALSE | LIT_CHAR;

function_body: '{' command_list '}';

command_list: command command_list | ;

command: TK_IDENTIFIER LEFT_ASSIGN expression;

expression: LIT_INTEGER | TK_IDENTIFIER | expression '+' expression | '(' expression ')';

%%

#include <stdio.h>
#include <stdlib.h>

extern int getLineNumber();

int yyerror()
{
  fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
  //exit(3);
}
