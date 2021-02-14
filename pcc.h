#include<ctype.h>
#include<stdarg.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// tokenizer
typedef enum {
  TK_RESERVED,
  TK_NUM,
  TK_EOF,
} TokenKind;
