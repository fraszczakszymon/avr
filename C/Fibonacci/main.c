#include <stdio.h>

long fibRec(long n)
{
  if (n==0) return 0;
  if (n==1) return 1;
  return fibRec(n-1) + fibRec(n-2);
}

long fibLin(long n)
{
  if (n==0) return 0;
  long a=0, b=1, temp, i;
  for (i=0; i<n-1; i++) {
    temp = b;
    b = a + b;
    a = temp;
  }
  return b;
}

int main()
{
  printf("Result: %ld", fibLin(75));
  return 0;
}