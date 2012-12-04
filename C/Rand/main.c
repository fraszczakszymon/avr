#include <stdio.h>
#include <string.h>

int main()
{
  char test[] = {"This is a simple string"};
  char *change;
  change = strstr(test, "simple");
  strncpy(change, "sample", 6);
  printf("%s\n\n", test);
  int seed = time(NULL);
  srand(seed);
  printf("Random numbers: %d %d %d %d %d\n", rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100);

  // getchar();
  return 0;
}