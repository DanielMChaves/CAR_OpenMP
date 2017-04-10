
// prueba3.c
// pruebas de "valgrind": memory leaks (cs.wisc.edu)
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int i;
  int *a;

  for (i=0; i<10; i++)
    a = malloc(100 * sizeof(int));

  free(a);

  return 0;
}
