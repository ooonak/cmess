#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STACKSIZE 10

int top=-1;
int stack[STACKSIZE];

#define push(i) stack[++top]=i
#define pop() stack[top--]

void popall()
{
  while(top != -1) {
    printf("[%d] = ", top);
    printf("%d\n", pop());
  }
}

int main()
{
  char* input;

  for (; fgets(input, 10, stdin) != NULL; ) {
    if (strstr(input, "pop")) {
      popall();
    } else {
      push(atoi(input));
      printf("push(%d)\n", atoi(input));
    }
  }

  return 0;
}
