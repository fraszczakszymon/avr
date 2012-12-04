#include <stdio.h>

long factorialRecursive(long n)
{
  if (n==1 || n==0) return 1;
  return n*factorialRecursive(n-1);
}

int main()
{
  printf("Result: %ld\n", factorialRecursive(5));

  return 0;
}