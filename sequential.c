#include <stdio.h>
#include <stdlib.h>
#include "common/maclaurin/maclaurin.h"

double PI = 0;

void compute_pi(unsigned int n)
{
    double pi = 0;
    for (unsigned int i=0; i<n; i++)
    {
        PI += maclaurin_polynomial_for_PI(i);
    }

    PI *= 4;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Invalid argument count\n");
        return 1;
    }

    unsigned int n = (unsigned int) atoi(argv[1]);
    compute_pi(n);
    printf("PI: %f", PI);

    return 0;
}