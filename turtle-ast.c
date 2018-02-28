#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}

struct ast_node *make_forward(struct ast_node* self) {
  self->kind = KIND_CMD_SIMPLE;
  self->u.cmd = CMD_FORWARD;
  return self;
}

void ast_destroy(struct ast *self) {

}

/*
 * context
 */

void context_create(struct context *self) {

}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {

}

/*
 * print
 */

void ast_print(const struct ast *self) {

  ast_node_print(self->unit);

}

void ast_node_print(const struct ast_node *self) {

  switch(self->kind) {
    case KIND_EXPR_VALUE:
      printf("%f\n", self->u.value);
      break;
    case KIND_CMD_SIMPLE:
      switch(self->u.cmd) {
        case CMD_FORWARD:
          printf("forward \n");
          ast_node_print(self->children[0]);
          break;
      }
      break;
  }

}
