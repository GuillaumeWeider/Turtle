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

struct ast_node *make_cmd_simple_noParam(enum ast_cmd cmd) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = cmd;
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_simple_1Param(struct ast_node* children, enum ast_cmd cmd) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = cmd;
  node->children_count = 1;
  node->children[0] = children;
  return node;
}

struct ast_node *make_cmd_simple_2Param(struct ast_node* children1, struct ast_node* children2, enum ast_cmd cmd) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = cmd;
  node->children_count = 2;
  node->children[0] = children1;
  node->children[1] = children2;
  return node;
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
  //Mettre à jour le ctx et faire des printf (lineTo, moveTo, color)
}

/*
 * print
 */

void ast_print(const struct ast *self) {

  ast_node_print(self->unit);
  printf("\n\n");
}

void ast_node_print(const struct ast_node *self) {

  switch(self->kind) {
    case KIND_EXPR_VALUE:
      printf("%f ", self->u.value);
      break;
    case KIND_CMD_SIMPLE:
      switch(self->u.cmd) {
        case CMD_FORWARD:
          printf("\nforward ");
          ast_node_print(self->children[0]);
          break;
        case CMD_BACKWARD:
          printf("\nbackward ");
          ast_node_print(self->children[0]);
          break;
        case CMD_POSITION:
          printf("\nposition ");
          ast_node_print(self->children[0]);
          ast_node_print(self->children[1]);
          break;
        case CMD_UP:
          printf("\nup");
          break;
        case CMD_DOWN:
          printf("\ndown");
          break;
        case CMD_PRINT:
          printf("\nprint ");
          ast_node_print(self->children[0]);
          break;
        case CMD_RIGHT:
          printf("\nright ");
          ast_node_print(self->children[0]);
          break;
        case CMD_LEFT:
          printf("\nleft ");
          ast_node_print(self->children[0]);
          break;
        case CMD_HEADING:
          printf("\nheading ");
          ast_node_print(self->children[0]);
          break;
        case CMD_COLOR:
          printf("\ncolor ");
          ast_node_print(self->children[0]);
          break;
      }
      break;
  }
  if(self->next != NULL) {
    ast_node_print(self->next);
  }

}
