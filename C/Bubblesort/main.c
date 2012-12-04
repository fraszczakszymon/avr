#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int array[], int n)
{
  int i, j, temp, changed=1;
  while (changed==1) {
    changed = 0;
    for (j=0; j<n; j++) {
      if (array[j] > array[j+1]) {
        temp = array[j+1];
        array[j+1] = array[j];
        array[j] = temp;
        changed = 1;
      }
    }
  }
}

int main()
{
  int i, array[8] = {4,6,5,2,3,9,5,7};
  int n = sizeof(array)/sizeof(int);
  bubbleSort(array, n);

  for (i=0; i<sizeof(array)/sizeof(int); i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
  return 0;
}