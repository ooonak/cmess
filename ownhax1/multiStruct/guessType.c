#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Write a program that try to gues wich type (simple) the user entered */

/* The types I can gues */
enum typeTag { INT, CHAR, DOUBLE };

/* Datattype to hold tokeni read from line */
struct token {
  char type;
  char string[10];
};

struct token stack[10];
struct token this;

/* Implement push/pop for the stack */
#define pop stack[top--]
#define push(s) stack[++top]=s

int getToken()
{
  /* Read tokens from input */
  char *p = this.string;
  while (((*p = getchar()) == ' '))
  ;
    if (isalnum(*p)) {
      while(isalnum(*++p = getchar()));
      ungetc(*p, stdin);
      *p = '\0';
      return 1;
    }
    return 0;
}

int main()
{
  printf("Please write some input (simple types), and let me see if I can guess the data type:\n");

  while(gettoken()) {
    push(this);
    this++;
  }

  return 0;
}
