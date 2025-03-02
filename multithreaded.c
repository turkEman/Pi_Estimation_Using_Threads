#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

long double PI = 0;
lock_t mutex = LOCK_INIT;

struct thread_task_args
{
    unsigned int start;
    unsigned int end;
};

void *thread_task(void *arg)
{
    struct thread_task_args *args = (struct thread_task_args *)arg;

    printf("\ns: %d, e: %d", args->start, args->end);
    printf("\n");

    for (unsigned int i = args->start; i <= args->end; i++)
    {
        acquire(&mutex);
        PI += maclaurin_polynomial_for_PI(i);
        release(&mutex);
    }

    free((void *)args);
    return NULL;
}

int main(int argc, char *argv[])
{
    // name of exe, number of threads, n
    if (argc != 3)
    {
        perror("Invalid argument count\n");
        return 1;
    }

    unsigned int no_of_threads = (unsigned int)atoi(argv[1]);
    unsigned int no_of_terms = (unsigned int)atoi(argv[2]);

    printf("Thread count: %d", no_of_threads);
    printf("\nn: %d", no_of_terms);

    if (no_of_terms < 1 || no_of_threads < 1)
    {
        perror("Invalid inputs\n");
        return 1;
    }

    pthread_t *threads = (pthread_t *)malloc(no_of_threads * sizeof(pthread_t));

    unsigned int div_each = no_of_terms / no_of_threads;
    unsigned int mod_remain = no_of_terms % no_of_threads;

    unsigned int start = 0;

    for (unsigned int i = 0; i < no_of_threads; i++)
    {
        struct thread_task_args *args = (struct thread_task_args *)malloc(sizeof(struct thread_task_args));
        if (!args)
        {
            perror("Memoory allocation falied for thread args\n");
            return 1;
        }
        args->start = start;
        args->end = args->start + (div_each - 1);

        if (i < mod_remain)
            args->end++;

        if (pthread_create(&threads[i], NULL, thread_task, (void *)args))
        {
            perror("Error creating thread %d" + i);
            free((void *)args);
            return 1;
        }

        start = args->end + 1;
    }

    for (unsigned int i = 0; i < no_of_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    free((void *)threads);

    PI *= 4;

    printf("\n\nPI is: %.20Lf", PI);
    printf("\n");

    return 0;
}