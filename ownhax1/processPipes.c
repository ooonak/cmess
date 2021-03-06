#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
 FILE* fpin;
 FILE* fpout;
 int input_fd[2];
 int output_fd[2];
 pid_t pid;
 int status;
 char input[100];
 char output[100];
 char *args[] = {"/somepath/someprogram", NULL};
 fgets(input, 100, stdin); // the user inputs the program name to exec

 pipe(input_fd);
 pipe(output_fd);
 pid = fork();

 if (pid == 0) {
  close(input_fd[1]);
  close(output_fd[0]);
  dup2(input_fd[0], 0);
  dup2(output_fd[1], 1);
  input[strlen(input)-1] = '\0';
  execvp(input, args);
 }
 else {
  close(input_fd[0]);
  close(output_fd[1]);
  fpin = fdopen(input_fd[1], "w");
  fpout = fdopen(output_fd[0], "r");
  while(!feof(fpout)) {
   fgets(output, 100, fpout);
   printf("output: %s\n", output);
  }
 }

 return 0;
}
