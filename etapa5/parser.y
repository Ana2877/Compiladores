%{
    #include "ast.h"
    #include "semantic.h"
    int getLineNumber(void);
    int yylex();
    int yyerror();
    AST* Root = NULL;
%}

%union
{
    HASH_NODE *symbol;
    AST *ast;
}


%token<symbol> KW_CHAR
%token<symbol> KW_INT
%token<symbol> KW_BOOL
%token<symbol> KW_POINTER

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
%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEGER
%token<symbol> LIT_TRUE
%token<symbol> LIT_FALSE
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%type<ast> program
%type<ast> declaration_list
%type<ast> declaration
%type<ast> variable_not_initialized
%type<ast> variable_initialized
%type<ast> array
%type<ast> array_not_initialized
%type<ast> array_initialized
%type<ast> array_with_expression
%type<ast> type
%type<ast> literal
%type<ast> literal_list
%type<ast> function
%type<ast> function_header
%type<ast> function_parameters
%type<ast> function_call
%type<ast> parameter_list
%type<ast> parameter
%type<ast> command_block
%type<ast> command_list
%type<ast> command
%type<ast> assign
%type<ast> assign_variable
%type<ast> assign_variable_right
%type<ast> assign_variable_left
%type<ast> assign_array
%type<ast> assign_array_right
%type<ast> assign_array_left
%type<ast> read
%type<ast> print
%type<ast> print_list
%type<ast> printable_variable
%type<ast> return
%type<ast> expression_list
%type<ast> expression
%type<ast> if_then
%type<ast> if_then_else
%type<ast> while


%left '|' '&'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'
%left '~' '#' '$'

%%
program: declaration_list                                     { $$ = $1; Root = $$; /*astPrint(Root, 0)*/; check_and_set_declarations(Root); check_undeclared(); check_operands(Root);};
declaration_list: declaration ';' declaration_list            { $$ = astCreate(AST_DECLARATION_LIST, 0, $1, $3, 0, 0);}
                  |                                           { $$ = 0; };
/* Declaration */
declaration: variable_initialized   { $$ = $1;}
            | array                 { $$ = $1;}
            | function              { $$ = $1;};


/* Variable declaration */
variable_not_initialized: type TK_IDENTIFIER                    { $$ = astCreate(AST_VARIABLE_NOT_INITIALIZED, 0, $1, astCreateSymbol($2), 0, 0);};
variable_initialized: variable_not_initialized ':' literal      { $$ = astCreate(AST_VARIABLE_INITIALIZED, 0, $1, $3, 0, 0);};


/* Array declaration */
array: array_initialized                                   { $$ = $1; }
      | array_not_initialized                              { $$ = $1; };
array_not_initialized: type '[' LIT_INTEGER ']' TK_IDENTIFIER   { $$ = astCreate(AST_ARRAY_NOT_INITIALIZED, 0, $1, astCreateSymbol($3), astCreateSymbol($5), 0);};
array_initialized: array_not_initialized ':' literal_list       { $$ = astCreate(AST_ARRAY_INITIALIZED, 0, $1, $3, 0, 0);};
array_with_expression: TK_IDENTIFIER '[' expression ']'         { $$ = astCreate(AST_ARRAY_WITH_EXPRESSION, 0, astCreateSymbol($1), $3, 0, 0);};


/* types */
type: KW_CHAR                                             { $$ = astCreateSymbol($1); }
      | KW_INT                                            { $$ = astCreateSymbol($1); }
      | KW_BOOL                                           { $$ = astCreateSymbol($1); }
      | KW_POINTER                                        { $$ = astCreateSymbol($1); };


/* literals, except string */
literal: LIT_INTEGER                                      { $$ = astCreateSymbol($1); }
        | LIT_TRUE                                        { $$ = astCreateSymbol($1); }
        | LIT_FALSE                                       { $$ = astCreateSymbol($1); }
        | LIT_CHAR                                        { $$ = astCreateSymbol($1); };
literal_list: literal literal_list                        { $$ = astCreate(AST_LITERAL_LIST, 0, $1, $2, 0, 0);}
              |                                           { $$ = 0; };


/* Functions */
function: function_header command_block                   { $$ = astCreate(AST_FUNCTION, 0, $1, $2, 0, 0);}
function_header: type TK_IDENTIFIER function_parameters   { $$ = astCreate(AST_FUNCTION_HEADER, 0, $1, astCreateSymbol($2), $3, 0);};
function_parameters: '(' parameter parameter_list ')'     { $$ = astCreate(AST_FUNCTION_PARAMETERS, 0, $2, $3, 0, 0);}
                      | '('')'                            { $$ = 0;};
function_call: TK_IDENTIFIER '(' expression expression_list ')'     { $$ = astCreate(AST_FUNCTION_CALL, 0, astCreateSymbol($1), $3, $4, 0);}
                | TK_IDENTIFIER '('')'                              { $$ = astCreate(AST_FUNCTION_CALL_NO_PARAMS, 0, astCreateSymbol($1), 0, 0, 0);};


/* Parameters */
parameter_list: ',' parameter parameter_list              { $$ = astCreate(AST_PARAMETER_LIST, 0, $2, $3, 0, 0);}
                |                                         { $$ = 0;};
parameter: variable_not_initialized                       { $$ = $1;};


/* Command Block */
command_block: '{' command_list '}'         { $$ = astCreate(AST_COMMAND_BLOCK, 0, $2, 0, 0, 0);};
command_list: command ';' command_list      { $$ = astCreate(AST_COMMAND_LIST, 0, $1, $3, 0, 0);}
              |                             { $$ = 0; };
command: command_block    {$$ = $1;}
        | assign          {$$ = $1;}
        | read            {$$ = $1;}
        | print           {$$ = $1;}
        | return          {$$ = $1;}
        | if_then         {$$ = $1;}
        | if_then_else    {$$ = $1;}
        | while           {$$ = $1;}
        |                 {$$ = 0;};


/* Assign */
assign: assign_variable                                                { $$ = $1;}
        | assign_array                                                 { $$ = $1;};

assign_variable: assign_variable_right                                 { $$ = $1;}
                  | assign_variable_left                               { $$ = $1;};
assign_variable_right: expression RIGHT_ASSIGN TK_IDENTIFIER           { $$ = astCreate(AST_ASSIGN_VARIABLE_RIGHT, 0, $1, astCreateSymbol($3), 0, 0);};
assign_variable_left: TK_IDENTIFIER LEFT_ASSIGN expression             { $$ = astCreate(AST_ASSIGN_VARIABLE_LEFT, 0, astCreateSymbol($1), $3, 0, 0);};

assign_array: assign_array_right                                       { $$ = $1;}
              | assign_array_left                                      { $$ = $1;};
assign_array_right: expression RIGHT_ASSIGN array_with_expression      { $$ = astCreate(AST_ASSIGN_ARRAY_RIGHT, 0, $1, $3, 0, 0);};
assign_array_left: array_with_expression LEFT_ASSIGN expression        { $$ = astCreate(AST_ASSIGN_ARRAY_LEFT, 0, $1, $3, 0, 0);};


/* Read */
read: KW_READ TK_IDENTIFIER                               { $$ = astCreate(AST_READ, 0, astCreateSymbol($2), 0, 0, 0);};


/* Print */
print: KW_PRINT printable_variable print_list             { $$ = astCreate(AST_PRINT, 0, $2, $3, 0, 0);};
print_list: ',' printable_variable print_list             { $$ = astCreate(AST_PRINT_LIST, 0, $2, $3, 0, 0);}
            |                                             { $$ = 0; };
printable_variable: LIT_STRING                            { $$ = astCreateSymbol($1);}
                    | expression                          { $$ = $1;};


/* Return */
return: KW_RETURN expression                              { $$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0);};


/* Expressions */
expression_list: ',' expression expression_list   { $$ = astCreate(AST_EXPRESSION_LIST, 0, $2, $3, 0, 0);}
                  |                               { $$ = 0;};
expression: array_with_expression                 { $$ = $1; }
            | TK_IDENTIFIER                       { $$ = astCreateSymbol($1); }
            | LIT_CHAR                            { $$ = astCreateSymbol($1); }
            | LIT_INTEGER                         { $$ = astCreateSymbol($1); }
            | LIT_TRUE                            { $$ = astCreateSymbol($1); }
            | LIT_FALSE                           { $$ = astCreateSymbol($1); }
            | expression '+' expression           { $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0); }
            | expression '-' expression           { $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0); }
            | expression '*' expression           { $$ = astCreate(AST_MULTIPLY, 0, $1, $3, 0, 0); }
            | expression '/' expression           { $$ = astCreate(AST_DIVIDE, 0, $1, $3, 0, 0); }
            | expression '>' expression           { $$ = astCreate(AST_GT, 0, $1, $3, 0, 0); }
            | expression '<' expression           { $$ = astCreate(AST_LT, 0, $1, $3, 0, 0); }
            | expression '|' expression           { $$ = astCreate(AST_OR, 0, $1, $3, 0, 0); }
            | expression '&' expression           { $$ = astCreate(AST_AND, 0, $1, $3, 0, 0); }
            | expression OPERATOR_LE expression   { $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); }
            | expression OPERATOR_GE expression   { $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }
            | expression OPERATOR_EQ expression   { $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }
            | expression OPERATOR_DIF expression  { $$ = astCreate(AST_DIF, 0, $1, $3, 0, 0); }
            | '~' expression                      { $$ = astCreate(AST_NOT, 0, $2, 0, 0, 0); }
            | '$' expression                      { $$ = astCreate(AST_DOLLAR, 0, $2, 0, 0, 0); }
            | '#' expression                      { $$ = astCreate(AST_HASHTAG, 0, $2, 0, 0, 0); }
            | function_call                       { $$ = $1; }
            | '(' expression ')'                  { $$ = astCreate(AST_PARENTHESIS, 0, $2, 0, 0, 0);};


/* Flow Control */
if_then: KW_IF '(' expression ')' KW_THEN command                           { $$ = astCreate(AST_IF, 0, $3, $6, 0, 0);};
if_then_else: KW_IF '(' expression ')' KW_THEN command KW_ELSE command      { $$ = astCreate(AST_IF_ELSE, 0, $3, $6, $8, 0);};
while: KW_WHILE '(' expression ')' command                                  { $$ = astCreate(AST_WHILE, 0, $3, $5, 0, 0);};

%%

#include <stdio.h>
#include <stdlib.h>

extern int getLineNumber();

int yyerror()
{
  fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
  exit(3);
}
