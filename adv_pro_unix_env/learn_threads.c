#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

static volatile int escape = 0;

struct thread_arg {
        unsigned long t;
        int b;
};

pthread_t t1, t2;

/* Singal handler */
void sig_handler(int value)
{
        printf("\tYou hit Ctrl+C, I'll tell thread 1 to cancel\n");
        escape = 1;
}

/* Thread cleanup handler */
void t_cleanup(void *arg)
{
        printf("\tCleanup %s\n", (char*) arg);
}

void *t_fn1(void *a)
{
        printf("\tThread %d (%lu) starting\n", (int) a, pthread_self());

        /* Push cleanup handler to stack */
        pthread_cleanup_push(t_cleanup, "thread 1");
        printf("\tThread %d pushed cleanup function\n", (int) a);

        /* Wait for a long time, we are cancelled anyway */
        printf("\tThread %d waiting 20 seconds\n", (int) a);

        int count = 10;

        while (count) {
                sleep(2);
                puts("\t.");
                count--;
        }

        /* Tell thread 2 that we are done, break his while loop */
        if (!escape) {
                printf("\tThread %d tell thread 2 to cancel\n", (int) a);
                pthread_cancel(t2);
        }

        /* Pop cleanup handler from stack */
        pthread_cleanup_pop(0);
        printf("\tThread %d popped cleanup function\n", (int) a);

        pthread_exit((void*) 1);
}

void *t_fn2(void *a)
{
        /* Typecast from void * to struct *, to get multiple arguments */
        struct thread_arg *b = (struct thread_arg *) a;

        printf("\tThread %d (%lu) starting\n", b->b, pthread_self());

        printf("\tThread %d registered signal handler, press Ctrl+C to cancel timer\n", b->b);
        signal(SIGINT, sig_handler);

        /* No SIGINT, just wait */
        while (!escape) {
                sleep(1);
        }

        /* If SIGINT cancel thread 1 */
        if (escape) {
                /* Cancel thread 1, activates its cleanup handler */
                printf("\tThread %d tell thread 1 to cancel\n", b->b);
                if ((pthread_cancel(b->t)) != 0)
                        printf("pthread_cancel error");
        }

        printf("\tThread %d exit\n", (int) b->b);

        /* Return '2' */
        pthread_exit((void*) 2);
        /* return (void*) NULL; */
}

int main()
{
        printf("Start from main()\n\n");

        void *t_ret;

        /* Thread 1, that implements cleanup handler */
        if (pthread_create(&t1, NULL, t_fn1, (void*) 1) != 0)
                printf("Could not create thread 1\n");

        /* Argument for thread 2 */
        struct thread_arg t2_arg = {
                t1, /* We set thread id of thread 1 */
                2
        };

        /* Thread 2, cancels thread 1 */
        if (pthread_create(&t2, NULL, t_fn2, (void*) &t2_arg) != 0)
                printf("Could not create thread 2\n");

        /* Handle thread 1 return */
        if ((pthread_join(t1, &t_ret)) != 0)
                printf("Can't join with thread 1");

        long ret = (long) t_ret;
        printf("\tThread 1 exit code %ld\n", ret);
        if (ret < 0)
                printf("\tThread 1 exits by cancel\n");
        else
                printf("\tThread 1 exits normally\n");

        /* Handle thread 2 return */
        if ((pthread_join(t2, &t_ret)) != 0)
                printf("Can't join with thread 2");

        ret = (long) t_ret;
        printf("\tThread 2 exit code %ld\n", ret);
        if (ret < 0)
                printf("\tThread 2 exits by cancel\n");
        else
                printf("\tThread 2 exits normally\n");

        printf("\nExit from main()\n");
        return 0;
}
