#include <stdio.h>

#ifndef _OPENMP
  #define omp_get_thread_num() 0
  #define omp_get_num_threads() 1
#endif

int main ()
{
  int nthr = 0;

  #ifdef _OPENMP
    #pragma omp parallel
  #endif
  {
    int tid = omp_get_thread_num();
    if(tid == 0){
      nthr = omp_get_num_threads();
      printf("Hola mundo, soy el hilo %d de %d hilos\n", tid, nthr);
    }
    printf("Hola mundo, soy el hilo %d\n", tid);
  }

  printf("Fin de hola mundo, soy el hilo %d\n", omp_get_thread_num());
}
