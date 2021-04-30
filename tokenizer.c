#include "pcc.h"

void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

void error_at(char *loc, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  // the num of byte of already read
  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, " ");
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

bool consume(char *op) {
  if (token->kind != TK_RESERVED || strlen(op) != token->len || memcmp(token->str, op, token->len)) {
    return false;
  }
  token = token->next;
  return true;
}

void expect(char *op) {
  if (token->kind != TK_RESERVED ||
      strlen(op) != token->len ||
      memcmp(token->str, op, token->len))
    error_at(token->str, "expexted %s", op);
  token = token->next;
}

int expect_number() {
  if (token->kind != TK_NUM)
    error_at(token->str, "Error: cannot tokenize");
  int val = token->val;
  token = token->next;
  return val;
}

bool at_eof() {
  return token->kind == TK_EOF;
}

Token *new_token(TokenKind kind, Token *cur, char *str, char *start, char *end) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  cur->next = tok;
  tok->len = end - start;
  return tok;
}

bool startswith(char *p, char *q) {
  return memcmp(p, q, strlen(q)) == 0;
}

// arg is input
Token *tokenize(char *p) {
  Token head;
  head.next = NULL;
  Token *cur = &head;

  while (*p) {

    // if exists one-line comments
    if (startswith(p, "//")) {
      p += 2;
      while (*p != '\n') {
        p++;
      }
      continue;
    }

    // if exists block comments
    if (startswith(p, "/*")) {
      char *q = strstr(p+2, "*/");
      if (!q) {
        error_at(p+2, "unclosed blocked comment");
      }
      p = q + 2;
      continue;
    }

    // skip new line
    if (*p== '\n') {
      p += 1;
      continue;
    }

    // skip whitespace
    if (isspace(*p)) {
      p++;
      continue;
    }

    // body of tokenizer

    // punctuator
    if (startswith(p, "==") || startswith(p, "!=") ||
        startswith(p, "<=") || startswith(p, ">=")) {
      cur = new_token(TK_RESERVED, cur, p, p, p+2);
      p += 2;
      continue;
    }

    if (strchr("+-*/()<>", *p)) {
      // p++ return the val of *p
      cur = new_token(TK_RESERVED, cur, p++, p, p+1);
      continue;
    }

    if (isdigit(*p)) {
      cur = new_token(TK_NUM, cur, p, p, p);
      char *q = p;
      cur->val = strtol(p, &p, 10);
      cur->len = p - q;
      continue;
    }

    if ('a' <= *p && *p <= 'z') {
      cur = new_token(TK_IDENT, cur, p++, p, p+1);
      continue;
    }
    
    error_at(token->str, "Error: cannot tokenize");
  }
  new_token(TK_EOF, cur, p, p, p);
  return head.next;
}
