#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "common/maclaurin/maclaurin.h"
#include "common/locks/locks.h"

void child_func(int start, int end, long double *PI, lock_t *mutex)
{
    long double local_sum = 0.0L;
    for (int i = start; i <= end; i++)
    {
        local_sum += maclaurin_polynomial_for_PI(i);
    }

    acquire(mutex);
    *PI += local_sum; // Write to shared memory
    release(mutex);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid argument count\n");
        return 1;
    }

    int no_of_child = atoi(argv[1]);
    int no_of_terms = atoi(argv[2]);

    if (no_of_child < 1 || no_of_terms < 1)
    {
        printf("Number of processes and terms should be at least 1.\n");
        return 1;
    }

    // Allocate shared memory
    long double *PI = mmap(NULL, sizeof(long double), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    lock_t *mutex = mmap(NULL, sizeof(lock_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    if (PI == MAP_FAILED || mutex == MAP_FAILED)
    {
        perror("mmap error");
        return 1;
    }

    *PI = 0.0L;
    *mutex = (lock_t)LOCK_INIT;

    int div_each = no_of_terms / no_of_child;
    int mod_remain = no_of_terms % no_of_child;
    int start = 0;

    for (int i = 0; i < no_of_child; i++)
    {
        int end = start + div_each - 1;
        if (i < mod_remain)
            end++;

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork error");
            return 1;
        }
        else if (pid == 0)
        { // Child process
            child_func(start, end, PI, mutex);
            exit(0);
        }
        start = end + 1;
    }

    // Parent waits for all children to finish
    for (int i = 0; i < no_of_child; i++)
    {
        wait(NULL);
    }

    *PI *= 4;

    
    munmap(PI, sizeof(long double));
    munmap(mutex, sizeof(lock_t));
    
    printf("\n\nPI is: %.20Lf\n", *PI);

    return 0;
}
