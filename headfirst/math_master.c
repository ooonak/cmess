#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int score = 0;

// A signal handler.
void end_game(int sig)
{
  printf("\nFinal score: %i\n", score);
  exit(0);
}

// This function register a handler.
int catch_signal(int sig, void (*handler)(int))
{
  // Create a new action.
  struct sigaction action;
  // This is the name of the function you wan't the computer to call.
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction (sig, &action, NULL);
}

void times_up(int sig)
{
  puts("\nTimes up!");
  raise(SIGINT);
}

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int main()
{
  // If we catch SIGALRM call times_up.
  catch_signal(SIGALRM, times_up);
  // If we catch SIGINT (Ctrl+c) call end_game.
  catch_signal(SIGINT, end_game);
  srandom (time (0));
  while (1) {
    int a = random() % 11;
    int b = random() % 11;
    char txt[4];

    // Set alarm to 5 second countdown.
    alarm(5);
    printf("What is %i times %i?", a, b);
    fgets(txt, 4, stdin);
    // Typecast 'string' to int.
    int answer = atoi(txt);
    if (answer == a * b)
      score++;
    else
      printf("\nWrong! Score: %i\n", score);
  }
  return 0;
}
