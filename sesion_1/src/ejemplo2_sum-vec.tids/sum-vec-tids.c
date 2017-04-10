#include <stdio.h>

int vec[8] = {1, 10, 100, 1000, 1, 10, 100, 1000};

int main ()
{
  int suma = 0;
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();
    suma += vec[tid];
  }
  printf("El resultado es %d\n", suma);
}
