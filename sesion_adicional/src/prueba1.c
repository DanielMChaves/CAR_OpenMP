
// prueba1.c
// pruebas de "valgrind": reading/writing past the end of an array (cs.wisc.edu)
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int i;
  int *a = malloc(10 * sizeof(int));
  if (!a)
    return -1; // fallo al pedir memoria
  for (i=0; i<=10; i++) {
    a[i] = i;
    // printf("i=%d\n", i);
  }
  free (a);
  return 0;
}
