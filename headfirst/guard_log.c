#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* now()
{
  time_t t;
  time (&t);
  return asctime(localtime (&t));
}

int main()
{
  char comment[80];
  char cmd[120];

  // Read into comment, max 79 characters, from stdin.
  fgets(comment, 80, stdin);

  // Print the character as a "command" string, that appends each string to a file.
  sprintf(cmd, "echo '%s %s' >> reports.log", comment, now());

  system(cmd);
  return 0;
}
