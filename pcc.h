#include<ctype.h>
#include<stdarg.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


// tokenizer
typedef enum {
  TK_PUNCT, // for punctuators
  TK_RESERVED, // for grammertical signature
  TK_IDENT, // for local variables
  TK_NUM, // for number
  TK_EOF, // eof signature
} TokenKind;

typedef struct Token Token;

struct Token {
  TokenKind kind;
  Token *next;
  int val;
  char *str;
  int len; // token length
  char *loc; // token location
};

void verror_at(char *loc, char *fmt, va_list ap);
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);

void expect(char *op);
int expect_number();
bool at_eof();
Token *new_token(TokenKind kind, char *str, char *start, char *end);
bool startswith(char *p, char *q);
Token *tokenize();

// parser
// parser
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_NEG, // unary -
  ND_NUM, // Integer
  ND_ASSIGN, // =
  ND_VAR, // local variable
  ND_EQ, // ==
  ND_NE, // !=
  ND_LT, // <
  ND_LE, // <=
  ND_EXPR_STMT, // statement
} NodeKind;

typedef struct Node Node;
struct Node {
  NodeKind kind;
  Node *lhs;   // lef,t hand side
  Node *rhs;   // right hand side
  Node *next;
  char name;   // if kind == ND_VAR
  int val;     // Node val
  int offset;  // stack offset for local variable
};

Node *parse(Token *tok);
Node *new_node(NodeKind kind);
Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);
Node *new_num(int val);


// BNF component
Node *expr(Token **rest, Token *tok);
Node *expr_stmt(Token **rest, Token *tok);
Node *assign(Token **rest, Token *tok);
Node *equality(Token **rest, Token *tok);
Node *relational(Token **rest, Token *tok);
Node *add(Token **rest, Token *tok);
Node *mul(Token **rest, Token *tok);
Node *unary(Token **rest, Token *tok);
Node *primary(Token **rest, Token *tok);

// code gen
void generator(Node *node);
void gen_expr(Node *node);


// global
char *current_input;
Token *token;
