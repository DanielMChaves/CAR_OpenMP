/* Programa que calula el n-esimo termino de la serie de Fibonacci */
/* Argumentos de entrada: N                                        */
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

/* Funcion que calcula el n-esimo termino de la serie de Fibonacci */

double fib(int n)
{
  double x, y;
  if (n < 2) return n;

  if (n > 30){
    #pragma omp task shared(x)
    x = fib(n - 1);
    #pragma omp task shared(y)
    y = fib(n - 2);
    #pragma omp taskwait
  }
  else {
    x = fib(n - 1);
    y = fib(n - 2);
  }

  return (x + y);
}

int main(int argc, char **argv)
{
  double res;
  int i, n;
  int id_thread, nthreads;

  struct timeval t, t2;
  double segundos;

  n = atoi(argv[1]);

  gettimeofday(&t, NULL);

  #pragma omp parallel shared(res)
  {
    #pragma omp single
    res = fib(n);
  }

  gettimeofday(&t2, NULL);
  segundos = (((t2.tv_usec - t.tv_usec)/1000000.0f)  + (t2.tv_sec - t.tv_sec));

  printf("\nResultado = %20.f, Duracion total = %f segundos\n\n", res, segundos);
}
