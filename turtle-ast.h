#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd {
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_POSITION,
  CMD_UP,
  CMD_DOWN,
  CMD_PRINT,
  CMD_RIGHT,
  CMD_LEFT,
  CMD_HEADING,
  CMD_COLOR,
};

// internal functions
enum ast_func {
  FUNC_SIN,
  FUNC_COS,
  FUNC_TAN,
  FUNC_SQRT,
  FUNC_POW,
  FUNC_RANDOM,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  KIND_REPEAT,
  KIND_SET,
  KIND_PROC,
  KIND_CALL,
  KIND_BLOCK,

  KIND_EXPR_VALUE,
  KIND_EXPR_NAME,
  KIND_EXPR_BINOP,
  KIND_UNARY_MINUS,
  KIND_FUNC,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
  enum ast_kind kind; // kind of the node

  union {
    enum ast_cmd cmd;   // the command if it is simple (KIND_CMD_SIMPLE)
    double value;       // the value for literals
    char op;            // the operator for expressions
    const char *name;   // the name for procedures and variables
    enum ast_func func; // the command if
  } u;

  size_t children_count;  // the number of children of the node
  struct ast_node *children[AST_CHILDREN_MAX];  // the children of the node (arguments of commands, etc)
  struct ast_node *next;  // the next node in the sequence
};


// TODO: make some constructors to use in parser.y
// for example:
struct ast_node *make_expr_value(double value);
struct ast_node *make_expr_name(const char* name);

struct ast_node *make_cmd_simple_noParam(enum ast_cmd cmd);
struct ast_node *make_cmd_simple_1Param(struct ast_node* children, enum ast_cmd cmd);
struct ast_node *make_cmd_simple_2Param(struct ast_node* children1, struct ast_node* children2, enum ast_cmd cmd);
struct ast_node *make_cmd_simple_3Param(struct ast_node* children1, struct ast_node* children2, struct ast_node* children3, enum ast_cmd cmd);


struct ast_node *make_cmd_kind_1Param(struct ast_node* children,  enum ast_kind kind);
struct ast_node *make_cmd_kind_2Param(struct ast_node* children1, struct ast_node* children2,  enum ast_kind kind);
struct ast_node *make_cmd_kind_name_2Param(const char* children1, struct ast_node* children2,  enum ast_kind kind);

struct ast_node *make_expr_binop(struct ast_node* children1, struct ast_node* children2, char operator);

struct ast_node *make_function_1Param(struct ast_node* children, enum ast_func func);
struct ast_node *make_function_2Param(struct ast_node* children1, struct ast_node* children2, enum ast_func func);

double getAngle(double angle);
double validValue(double value);

// root of the abstract syntax tree
struct ast {
  struct ast_node *unit;
};

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(struct ast *self);

// the execution context
struct context {
  double x;
  double y;
  double angle;
  bool up;

  // TODO: add procedure handling
  // TODO: add variable handling
};

// create an initial context
void context_create(struct context *self);

// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);
void ast_node_print(const struct ast_node *self);

// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);
void ast_node_eval(const struct ast_node *self, struct context *ctx);

#endif /* TURTLE_AST_H */
