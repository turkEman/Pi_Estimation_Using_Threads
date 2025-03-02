#include "maclaurin.h"

long double maclaurin_polynomial_for_PI(unsigned int n)
{
    return ((n % 2) ? -1.0L : 1.0L) / (2 * n + 1);
}