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
program: declaration_list;
declaration_list: declaration recursive_declaration | ;
recursive_declaration: ';' declaration recursive_declaration |;

/* Declaration */
declaration: variable | array | function;


/* Variable declaration */
variable: variable_initialized | variable_not_initialized;
variable_not_initialized: type TK_IDENTIFIER;
variable_initialized: variable_not_initialized ':' literal;


/* Array declaration */
array: array_initialized | array_not_initialized;
array_not_initialized: type '[' LIT_INTEGER ']' TK_IDENTIFIER;
array_initialized: array_not_initialized ':' literal_list;
array_with_expression: TK_IDENTIFIER '[' expression ']';


/* types */
type: KW_CHAR | KW_INT | KW_BOOL | KW_POINTER;


/* literals, except string */
literal: LIT_INTEGER | LIT_TRUE | LIT_FALSE | LIT_CHAR;
literal_list: literal literal_list |;


/* Functions */
function: function_header function_body;
function_header: type TK_IDENTIFIER function_parameters;
function_parameters: '('parameter_list ')';
function_body: '{' command_list '}';


/* Parameters */
parameter_list: parameter recursive_parameter |;
recursive_parameter: ',' parameter recursive_parameter |;
parameter: variable_not_initialized;


/* Command Block */
command_list: command recursive_command |;
recursive_command: ';' command recursive_command |;


command: assign | read;

/* Assign */
assign: assign_variable | assign_array;

assign_variable: assign_variable_right | assign_variable_left;
assign_variable_right: expression RIGHT_ASSIGN TK_IDENTIFIER;
assign_variable_left: TK_IDENTIFIER LEFT_ASSIGN expression;

assign_array: assign_array_right | assign_array_left;
assign_array_right: expression RIGHT_ASSIGN array_with_expression;
assign_array_left: array_with_expression LEFT_ASSIGN expression;

/* Read */
read: KW_READ TK_IDENTIFIER;

/* Print */


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
