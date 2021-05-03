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
  int pos = loc - current_input;
  fprintf(stderr, "%s\n", current_input);
  fprintf(stderr, "%*s", pos, " ");
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

void expect(char *op) {
  if (token->kind != TK_RESERVED ||
      strlen(op) != token->len ||
      memcmp(token->str, op, token->len))
    error_at(token->str, "expexted %s", op);
  token = token->next;
}

Token *new_token(TokenKind kind, char *start, char *end) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->loc = start;
  tok->len = end - start;
  return tok;
}

bool startswith(char *p, char *q) {
  return memcmp(p, q, strlen(q)) == 0;
}

bool is_ident1(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

bool is_ident2(char c) {
  return is_ident1(c) || ('0' <= c && c <= '9');
}

int read_punct(char *p) {
  if (startswith(p, "==") || startswith(p, "!=") || startswith(p, "<=") || startswith(p, ">=")) {
    return 2;
  }
  return ispunct(*p) ? 1 : 0;
}

// arg is input
Token *tokenize(char *p) {
  Token head = {};
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

    if (isdigit(*p)) {
      cur->next = new_token(TK_NUM, p, p);
      cur = cur->next;

      char *q = p;
      cur->val = strtol(p, &p, 10);
      cur->len = p - q;
      continue;
    }

    // Identifier
    if (is_ident1(*p)) {
      char *start = p;
      do {
        p++;
      } while (is_ident2(*p));
      cur = cur->next = new_token(TK_IDENT, start, p);
      continue;
    }

    // Punctuators
    int punct_len = read_punct(p);
    if (punct_len) {
      cur = cur->next = new_token(TK_PUNCT, p, p+punct_len);
      p += cur->len;
      continue;
    }

    
    error_at(token->str, "Error: cannot tokenize");
  }

  cur->next = new_token(TK_EOF, p, p);
  cur = cur->next;

  return head.next;
}
