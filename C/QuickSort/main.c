#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void quickSort(int array[], int left, int right)
{
  if (left<right) {
    int i, position=left;

    for (i=left+1; i<=right; i++) {
      if (array[i]<array[left]) {
        swap(&array[++position], &array[i]);
      }
    }
    swap(&array[left], &array[position]);

    quickSort(array, left, position-1);
    quickSort(array, position+1, right);
  }
}

int main()
{
  int i;
  int array[24] = {6,3,12,3,524,2,1,2,5,0,23,1,2,5,5,1,3,7,8,9,3,4,5,23};//{4,6,5,2,3,9,5,7};
  int size = sizeof(array)/sizeof(int);
  quickSort(array, 0, size-1);

  for (i=0; i<sizeof(array)/sizeof(int); i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
  return 0;
}