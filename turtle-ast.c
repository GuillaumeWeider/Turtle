#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SCREEN_SIZE 1000

#define PI 3.141592653589793
#define SQRT2 1.41421356237309504880
#define SQRT3 1.7320508075688772935

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}

struct ast_node *make_expr_name(const char* name) {
    struct ast_node *node = calloc(1, sizeof(struct ast_node));
    node->kind = KIND_EXPR_NAME;
    node->u.name = name;
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

struct ast_node *make_cmd_simple_3Param(struct ast_node* children1, struct ast_node* children2, struct ast_node* children3, enum ast_cmd cmd) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = cmd;
  node->children_count = 3;
  node->children[0] = children1;
  node->children[1] = children2;
  node->children[2] = children3;
  return node;
}

struct ast_node *make_expr_binop(struct ast_node* children1, struct ast_node* children2, char operator) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_BINOP;
  node->u.op = operator;
  node->children_count = 2;
  node->children[0] = children1;
  node->children[1] = children2;
  return node;
}

struct ast_node *make_cmd_kind_1Param(struct ast_node* children,  enum ast_kind kind) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = kind;
  node->children_count = 1;
  node->children[0] = children;
  return node;
}

struct ast_node *make_cmd_kind_2Param(struct ast_node* children1, struct ast_node* children2,  enum ast_kind kind) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = kind;
  node->children_count = 2;
  node->children[0] = children1;
  node->children[1] = children2;
  return node;
}

struct ast_node *make_cmd_kind_name_2Param(const char* children1, struct ast_node* children2,  enum ast_kind kind) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = kind;
  node->children_count = 2;
  node->children[0] = make_expr_name(children1);
  node->children[1] = children2;
  return node;
}

struct ast_node *make_function_1Param(struct ast_node* children, enum ast_func func) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_FUNC;
  node->u.func = func;
  node->children_count = 1;
  node->children[0] = children;
  return node;
}


struct ast_node *make_function_2Param(struct ast_node* children1, struct ast_node* children2, enum ast_func func) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_FUNC;
  node->u.func = func;
  node->children_count = 2;
  node->children[0] = children1;
  node->children[1] = children2;
  return node;
}

double getAngle(double angle) {
  return (angle - 90);
}

double validValue(double value) {

  if(value < 0){
    return 0;
  }
  else if(SCREEN_SIZE < value){
    return SCREEN_SIZE;
  }
  else{
    return value;
  }
}


void ast_destroy(struct ast *self) {

}

/*
 * context
 */

void context_create(struct context *self) {

  self = calloc(1, sizeof(struct context));
  self->x = 0;
  self->y = 0;
  self->angle = 90;
  self->up = false;
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {

  ast_node_eval(self->unit, ctx);

}

double ast_node_eval(const struct ast_node *self, struct context *ctx) {
  //Mettre à jour le ctx et faire des printf (lineTo, moveTo, color)

  switch(self->kind) {
    case KIND_EXPR_VALUE:
      return self->u.value;
      break;
    case KIND_EXPR_NAME:

      break;
    case KIND_EXPR_BINOP:

        break;
    case KIND_UNARY_MINUS:

        break;
    case KIND_CMD_SIMPLE:
      switch(self->u.cmd) {
        case CMD_FORWARD:
          ctx->x = validValue(cos(getAngle(ctx->angle)) * ast_node_eval(self->children[0], ctx));
          ctx->y = validValue(sin(getAngle(ctx->angle)) * ast_node_eval(self->children[0], ctx));
          break;
        case CMD_BACKWARD:

          break;
        case CMD_POSITION:
          ctx->x = validValue(ast_node_eval(self->children[0], ctx));
          ctx->y = validValue(ast_node_eval(self->children[1], ctx));
          break;
        case CMD_UP:
          ctx->up = true;
          break;
        case CMD_DOWN:
          ctx->up = false;
          break;
        case CMD_PRINT:

          break;
        case CMD_RIGHT:

          break;
        case CMD_LEFT:

          break;
        case CMD_HEADING:

          break;
        case CMD_COLOR:

          break;
      }
      break;
    case KIND_REPEAT:

      break;
    case KIND_SET:

      break;
    case KIND_PROC:

      break;
    case KIND_CALL:

      break;
    case KIND_BLOCK:

      break;
    case KIND_FUNC:
      switch(self->u.func) {
        case FUNC_SIN:

          break;
        case FUNC_COS:

          break;
        case FUNC_TAN:

          break;
        case FUNC_SQRT:

          break;
        case FUNC_POW:

          break;
        case FUNC_RANDOM:

          break;
        }
        break;
  }
  if(self->next != NULL) {

  }
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
    case KIND_EXPR_NAME:
      printf("%s ", self->u.name);
      break;
    case KIND_EXPR_BINOP:
        printf("%c ", self->u.op);
        ast_node_print(self->children[0]);
        ast_node_print(self->children[1]);
        break;
    case KIND_UNARY_MINUS:
        printf("-");
        ast_node_print(self->children[0]);
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
          ast_node_print(self->children[1]);
          ast_node_print(self->children[2]);
          break;
      }
      break;
    case KIND_REPEAT:
      printf("repeat ");
      ast_node_print(self->children[0]);
      ast_node_print(self->children[1]);
      break;
    case KIND_SET:
      printf("set ");
      ast_node_print(self->children[0]);
      ast_node_print(self->children[1]);
      break;
    case KIND_PROC:
      printf("proc ");
      ast_node_print(self->children[0]);
      ast_node_print(self->children[1]);
      break;
    case KIND_CALL:
      printf("call ");
      ast_node_print(self->children[0]);
      break;
    case KIND_BLOCK:
      printf("{ ");
      ast_node_print(self->children[0]);
      printf(" }");
      break;
    case KIND_FUNC:
      switch(self->u.func) {
        case FUNC_SIN:
          printf("\nsin ");
          ast_node_print(self->children[0]);
          break;
        case FUNC_COS:
          printf("\ncos ");
          ast_node_print(self->children[0]);
          break;
        case FUNC_TAN:
          printf("\ntan ");
          ast_node_print(self->children[0]);
          break;
        case FUNC_SQRT:
          printf("\nsqrt ");
          ast_node_print(self->children[0]);
          break;
        case FUNC_POW:
          printf("\n");
          ast_node_print(self->children[0]);
          printf("^");
          ast_node_print(self->children[1]);
          break;
        case FUNC_RANDOM:
          printf("\nrandom [");
          ast_node_print(self->children[0]);
          printf(", ");
          ast_node_print(self->children[1]);
          printf("]");
          break;
        }
        break;
  }
  if(self->next != NULL) {
    ast_node_print(self->next);
  }

}
