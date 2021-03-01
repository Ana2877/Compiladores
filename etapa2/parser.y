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
recursive_declaration: ';' declaration recursive_declaration | ';';

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
function: function_header command_block;
function_header: type TK_IDENTIFIER function_parameters;
function_parameters: '(' parameter_list ')';
function_call: TK_IDENTIFIER '(' expression_list ')';


/* Parameters */
parameter_list: parameter recursive_parameter |;
recursive_parameter: ',' parameter recursive_parameter |;
parameter: variable_not_initialized;


/* Command Block */
command_block: '{' command_list '}';
command_list: command ';' command_list |;
command: assign | read | print | return | if_then | if_then_else | while | ;
command_or_command_list: command | command_block;


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
print: KW_PRINT print_list;
print_list: printable_variable recursive_print |;
recursive_print: ',' printable_variable recursive_print |;
printable_variable: LIT_STRING | expression;


/* Return */
return: KW_RETURN expression;


/* Operators */
operator: '+' | '-' | '*' | '/' | '<' | '>' | '|' | '&' | OPERATOR_LE | OPERATOR_GE | OPERATOR_EQ | OPERATOR_DIF;
unary_operator: '~' | '$' | '#';


/* Expressions */
expression_list: expression recursive_expression |;
recursive_expression: ',' expression recursive_expression |;
expression: array_with_expression |
            TK_IDENTIFIER |
            LIT_CHAR |
            LIT_INTEGER |
            expression '+' expression |
            expression '-' expression |
            expression '*' expression |
            expression '/' expression |
            expression '<' expression |
            expression '>' expression |
            expression '|' expression |
            expression '&' expression |
            expression OPERATOR_LE expression |
            expression OPERATOR_GE expression |
            expression OPERATOR_EQ expression |
            expression OPERATOR_DIF expression |
            '~' expression |
            '$' expression |
            '#' expression |
            function_call  |
            '(' expression ')';


/* Flow Control */
if_then: KW_IF '(' expression ')' KW_THEN command_or_command_list;
if_then_else: KW_IF '(' expression ')' KW_THEN command_or_command_list KW_ELSE command_or_command_list;
while: KW_WHILE '(' expression ')' command_or_command_list;

%%

#include <stdio.h>
#include <stdlib.h>

extern int getLineNumber();

int yyerror()
{
  fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
  //exit(3);
}
