%{
#include <stdio.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  const char *name;
  struct ast_node *node;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token            KW_UP        "up"
%token            KW_DOWN      "down"
%token            KW_FORWARD   "forward"
%token            KW_BACKWARD  "backward"
%token            KW_PRINT     "print"
%token            KW_RIGHT     "right"
%token            KW_LEFT      "left"
%token            KW_HEADING   "heading"
%token            KW_COLOR     "color"
%token            KW_POSITION  "position"

%token            KW_REPEAT    "repeat"
%token            KW_SIN       "sin"
%token            KW_COS       "cos"
%token            KW_TAN       "tan"
%token            KW_SQRT      "sqrt"
%token            KW_POW       "pw"
%token            KW_RANDOM    "random"

%left '+' '-'
%left '*' '/'
%left UMINUS

%type <node> unit cmds cmd expr_literal expr_primary expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_UP                      { $$ = make_cmd_simple_noParam(CMD_UP); }
  | KW_DOWN                    { $$ = make_cmd_simple_noParam(CMD_DOWN); }
  | KW_FORWARD expr            { $$ = make_cmd_simple_1Param($2, CMD_FORWARD); }
  | KW_BACKWARD expr           { $$ = make_cmd_simple_1Param($2, CMD_BACKWARD); }
  | KW_PRINT expr              { $$ = make_cmd_simple_1Param($2, CMD_PRINT); }
  | KW_RIGHT expr              { $$ = make_cmd_simple_1Param($2, CMD_RIGHT); }
  | KW_LEFT expr               { $$ = make_cmd_simple_1Param($2, CMD_LEFT); }
  | KW_HEADING expr            { $$ = make_cmd_simple_1Param($2, CMD_HEADING); }
  | KW_COLOR expr              { $$ = make_cmd_simple_1Param($2, CMD_COLOR); } /*Trois param ou une couleur et les virgules entre les expr*/
  | KW_POSITION expr ',' expr  { $$ = make_cmd_simple_2Param($2, $4, CMD_POSITION); }
  | KW_REPEAT expr ',' cmds    { $$ = make_repeat($2, $4); }
;

expr_literal:
      VALUE { $$ = make_expr_value($1); }
    | NAME  { $$ = make_expr_name($1);  }
;

expr_primary:
    expr_literal                        { $$ = $1; }
    | KW_SIN '(' expr ')'               { $$ = make_function_1Param($3, FUNC_SIN); }
    | KW_COS '(' expr ')'               { $$ = make_function_1Param($3, FUNC_COS); }
    | KW_TAN '(' expr ')'               { $$ = make_function_1Param($3, FUNC_TAN); }
    | KW_SQRT '(' expr ')'              { $$ = make_function_1Param($3, FUNC_SQRT); }
    | KW_POW '(' expr ',' expr ')'      { $$ = make_function_2Param($3, $5, FUNC_POW); }
    | KW_RANDOM '(' expr ',' expr ')'   { $$ = make_function_2Param($3, $5, FUNC_RANDOM); }
;

expr:
      expr_primary      { $$ = $1; }
      | expr '+' expr     { $$ = make_expr_binop($1, $3, '+'); }
      | expr '-' expr     { $$ = make_expr_binop($1, $3, '-'); }
      | expr '*' expr     { $$ = make_expr_binop($1, $3, '*'); }
      | expr '/' expr     { $$ = make_expr_binop($1, $3, '/'); }
      | '(' expr ')'        { $$ = $2; }
      | '-' expr %prec UMINUS { $$ = make_unary_minus($2, KIND_UNARY_MINUS);}
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
