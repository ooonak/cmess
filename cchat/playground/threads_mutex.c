#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

struct link{
  struct link *next;
  char *value;
};

int no_of_links = 0;
struct link *head_of_queue, *tail_of_queue;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int add_to_queue(char *value)
{
  pthread_mutex_lock(&lock);

  if (no_of_links == 0) {
    tail_of_queue = (struct link*) malloc(sizeof(struct link));
    tail_of_queue->next = NULL;
    head_of_queue = tail_of_queue;
  } else {
    struct link* tmp_link = (struct link*) malloc(sizeof(struct link));
    tmp_link->next = tail_of_queue;
    tail_of_queue = tmp_link;
  }

  tail_of_queue->value = (char*) malloc(strlen(value) + 1);
  strcpy(tail_of_queue->value, value);
  no_of_links++;

  pthread_mutex_unlock(&lock);

  return 0;
}

void print_queue(int free_mem)
{
  int i = 0;

  struct link *tmp_link = tail_of_queue;

  while(i < no_of_links) {
    printf("%d: \t- %s\n", i+1, tmp_link->value);

    if (free_mem)
      free(tmp_link->value);

    struct link *to_free = tmp_link;
    tmp_link = tmp_link->next;

    if (free_mem)
      free(to_free);

    i++;
  }
}

void *thread_function(void *para)
{
  char tmp_str[100];

  /*
  sprintf(tmp_str, "%d", index);
  int number_length = strlen(tmp_str);
  strncat(tmp_str, ": Thread talking...", 99 - number_length);
  */

  /* Cast from void pointer to int pointer and then get value */
  int id = *((int*) para);

  /* Get thread id */
  pthread_t tid = pthread_self();

  int j;
  for (j = 0; j < 3; j++) {
    sprintf(tmp_str, "Thread %d (%d) talking.", id, (int) tid);
    add_to_queue(tmp_str);
  }

  return NULL;
}

int main()
{
  /* Make three worker threads */
  pthread_t t0, t1, t2;
  int t0id = 0, t0rv = 9;
  int t1id = 1, t1rv = 8;
  int t2id = 2, t2rv = 7;

  if (pthread_create(&t0, NULL, thread_function, (void*) &t0id) == -1)
    puts("Creation of thread t0 failed\n");

  if (pthread_create(&t1, NULL, thread_function, (void*) &t1id) == -1)
    puts("Creation of thread t1 failed\n");

  if (pthread_create(&t2, NULL, thread_function, (void*) &t2id) == -1)
    puts("Creation of thread t2 failed\n");

  /* Wait for threads to join - can we get a deadlock here? */
  pthread_join(t0, (void**) &t0rv);
  pthread_join(t1, (void**) &t1rv);
  pthread_join(t2, (void**) &t2rv);

  /* Print return values */
  printf("All worker threads has returned: %d, %d, %d\n", t0rv, t1rv, t2rv);

  /* Also free if parameter = 1 */
  print_queue(1);

  return 0;
}
