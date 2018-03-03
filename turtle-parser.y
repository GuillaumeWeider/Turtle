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
    KW_UP                 { $$ = make_cmd_simple_noParam(CMD_UP); }
  | KW_DOWN               { $$ = make_cmd_simple_noParam(CMD_DOWN); }
  | KW_FORWARD expr       { $$ = make_cmd_simple_1Param($2, CMD_FORWARD); }
  | KW_BACKWARD expr      { $$ = make_cmd_simple_1Param($2, CMD_BACKWARD); }
  | KW_PRINT expr         { $$ = make_cmd_simple_1Param($2, CMD_PRINT); }
  | KW_RIGHT expr         { $$ = make_cmd_simple_1Param($2, CMD_RIGHT); }
  | KW_LEFT expr          { $$ = make_cmd_simple_1Param($2, CMD_LEFT); }
  | KW_HEADING expr       { $$ = make_cmd_simple_1Param($2, CMD_HEADING); }
  | KW_COLOR expr         { $$ = make_cmd_simple_1Param($2, CMD_COLOR); }
  | KW_POSITION expr expr { $$ = make_cmd_simple_2Param($2, $3, CMD_POSITION); }

;

expr_literal:
    VALUE { $$ = make_expr_value($1); }
    NAME  { $$ = make_expr_name($1);  }
    /* TODO: add identifier */
;

expr_primary:
    expr_literal        { $$ = $1; }
    /* TODO: add internal functions */
;

expr:
    expr_primary      { $$ = $1; }
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
