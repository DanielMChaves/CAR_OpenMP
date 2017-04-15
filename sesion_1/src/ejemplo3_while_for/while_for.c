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
  printf("(While): El primer cero esta en la posicion %d\n", i);

  /** Version for **/
  int res = -1;
  for (i = 0; i < N; i++) {
    if (a[i] == 0 && res < 0)
      res = i;
  }
  printf("(For - original): El primer cero esta en la posicion %d\n", res);

  int res1 = -1;
  #pragma omp parallel for firstprivate(res1)
  for (i = 0; i < N; i++) {
    if (a[i] == 0 && res1 < 0)
        res1 = i;
  }
  printf("(For - firstprivate): El primer cero esta en la posicion %d\n", res1);

  int res2 = -1;
  #pragma omp parallel for lastprivate(i)
  for (i = 0; i < N; i++) {
    if (a[i] == 0 && res2 < 0)
        res2 = i;
  }
  printf("(For - lastprivate): El primer cero esta en la posicion %d\n", res2);

  int res3 = N + 1;
  #pragma omp parallel for reduction(min:res3)
  for (i = 0; i < N; i++) {
    if (a[i] == 0 && res3 > N)
        res3 = i;
  }
  printf("(For - reduction): El primer cero esta en la posicion %d\n", res3);

  return(0);
}
