#include<stdio.h>
#ifndef _OPENMP
   #define omp_get_thread_num() 0
#endif

int main ()
{ 
#ifdef _OPENMP
  #pragma omp parallel
#endif
  {
    int tid = omp_get_thread_num();
    printf("Hola mundo, soy el hilo %d\n", tid);
  }
  printf("Fin de hola mundo, soy el hilo %d\n", omp_get_thread_num());
}

