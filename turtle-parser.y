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

%token            KW_FORWARD  "forward"
%token            KW_BACKWARD  "backward"
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
    KW_FORWARD expr       { $$ = make_cmd_fw_bw($2, CMD_FORWARD); }
  | KW_BACKWARD expr      { $$ = make_cmd_fw_bw($2, CMD_BACKWARD); }
  | KW_POSITION expr expr { $$ = make_cmd_position($2, $3); }
;

expr_literal:
    VALUE { $$ = make_expr_value($1); }
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
