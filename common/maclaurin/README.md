# Maclaurin Series Library

This folder contains the implementation of the Maclaurin series function used to approximate π in this project.

## Files

- **maclaurin.h**  
  Declares the function:
  - `long double maclaurin_polynomial_for_PI(unsigned int n);`  
    This function returns the nth term of the Maclaurin series for π.

- **maclaurin.c**  
  Implements the function declared in `maclaurin.h`.  
  The function computes each term as:
  ```c
  ((n % 2) ? -1.0L : 1.0L) / (2 * n + 1)

## Usage
Include maclaurin.h in your source files to access the maclaurin_polynomial_for_PI function.
The function is used in all four versions of the Pi estimation project to calculate the contribution of each term in the series.

## Note
The Maclaurin series for π approximates π/4. To obtain π, the sum of the series is multiplied by 4.