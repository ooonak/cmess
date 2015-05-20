#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

/*
 * 20 threads counting beer down. Remeber to link with pthread when you compile.
 */

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

// Define a "lock", actually a macro.
pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

int beers = 2000000;

void* drink_lots(void *a)
{
  int i;
  for (i=0; i < 100000; i++) {
    // MUTually EXclusive: lock down this variable, only one thread at a time.
    pthread_mutex_lock(&beers_lock);
    beers = beers - 1;
    // Unlock.
    pthread_mutex_unlock(&beers_lock);
  }
  printf("beers = %i\n", beers);
  return NULL;
}

int main()
{
  pthread_t threads[20];
  int t;
  printf("%i bottles of beer on the wall\n%i bottles of beer\n", beers, beers);

  for (t = 0; t < 20; t++) {
    if(pthread_create(&threads[t], NULL, drink_lots, NULL))
      error("Can't create thread.");
  }

  void* result;
  for (t = 0; t < 20; t++) {
    if(pthread_join(threads[t], &result))
      error("Can't join thread.");
  }

  printf("There are now %i bottles of beer on the wall\n", beers);
  return 0;
}
