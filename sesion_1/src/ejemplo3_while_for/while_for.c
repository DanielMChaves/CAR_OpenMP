/** Busca la posicion del vector "a" donde se encuentra el primer cero **/

#include <stdio.h>
#include <stdlib.h>

#define N 100

int a[N];

int main ()
{
  int i;

  for (i=0; i<N; i++)
    a[i] = i+1;

  a[N/2] = 0;
  a[N/4] = 0;

  /** Version while **/
  i = 0;
  while (a[i] != 0 && i < N){
	   i++;
  }
  printf("(While):El primer cero esta en la posicion %d\n", i);

  /** Version for **/
  int res = -1;
  for (i = 0; i < N; i++) {
    if (a[i] == 0 && res < 0)
        res = i;
  }
  printf("(For): El primer cero esta en la posicion %d\n", res);

  return(0);
}
