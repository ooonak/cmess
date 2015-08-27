#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

/* Init barrier */
pthread_barrier_t start_barrier;
pthread_barrier_t end_barrier;
unsigned start_count;
unsigned end_count;

pthread_rwlock_t rwlock;

int var;

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}

void* read_m(void *a)
{
  pthread_barrier_wait(&start_barrier);
  pthread_rwlock_rdlock(&rwlock);

  pthread_t t_id = pthread_self();

  /* Do work */
  printf("Reader thread %lu active: var = %d\n", t_id, var);
  sleep(1);

  pthread_rwlock_unlock(&rwlock);
  pthread_barrier_wait(&end_barrier);
  return NULL;
}

void* write_m(void *a)
{
  pthread_barrier_wait(&start_barrier);
  pthread_rwlock_wrlock(&rwlock);

  pthread_t t_id = pthread_self();

  printf("Writer thread %lu active\n", t_id);
  var += 221;

  pthread_rwlock_unlock(&rwlock);
  pthread_barrier_wait(&end_barrier);
  return NULL;
}

int main()
{
  var = 100;

  pthread_t reader_t[10];
  pthread_t writer_t;

  /* Implement barrier, 11 threads must join before we raise start barrier */
  start_count = 11;
  pthread_barrier_init(&start_barrier, NULL, start_count);

  /* Implement barrier, 12 threads must join before we raise end barrier */
  end_count = 12;
  pthread_barrier_init(&end_barrier, NULL, end_count);

  /* Implement rw lock */
  pthread_rwlock_init(&rwlock, 0);

  /* Make writer thread */
  if (pthread_create(&writer_t, NULL, write_m, NULL))
    error("Can't create writer thread.");
  printf("Created writer thread\n");

  usleep(500);

  /* Make 10 reader threads */
  int i;
  for (i = 0; i < 10; i++) {
    if (pthread_create(&reader_t[i], NULL, read_m, NULL))
      error("Can't create reader thread.");
    printf("Created reader thread %d\n", i);
  }

  /* Wait for all threads to finish and join end barrier */
  sleep(1);
  pthread_barrier_wait(&end_barrier);

  /* Destroy barriers */
  printf("Main cleaning up\n");
  pthread_barrier_destroy(&start_barrier);
  pthread_barrier_destroy(&end_barrier);

  /* Destroy rw lock */
  pthread_rwlock_destroy(&rwlock);

  return 0;
}
