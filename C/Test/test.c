#include <stdio.h>
#include <string.h>
#include "b.h"

int main()
{
  char imie[32];
  int a,b;
  printf("Podaj imie: ");
  scanf("%s", imie);

  printf("Witaj %s\nLiczba znakow w imieniu: %d\n", imie, strlen(imie));
  printf("Podaj liczby ktore chcesz dodac:\n");
  scanf("%d", &a);
  scanf("%d", &b);
  int c;
  c = add(a, b);
  printf("Wynik dodawania to: %d\n", c);

  return 0;
}