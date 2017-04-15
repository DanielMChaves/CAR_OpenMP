/*** Probamos threadprivate, copyin y schedule             ***/
/*** Version paralela inicial                              ***/
/** Argumentos: #filas_matriz cte_inicializacion_matrices  ***/
/*************************************************************/

#include <stdio.h>
#include <omp.h>

static int contador = 0;
static int cte= 20; // Puede tomar cualquier valor si no se inicializa

/** Imprime una matriz en pantalla **/
void ImprimirMatriz (float *M, int n){
    int i, j;
    for (i = 0;i<n;i++){
      for (j = 0;j<n;j++){
        printf(" %f ", M[i*n+j]);
      }
      printf("\n");
    }
}

int main (int argc, char **argv)
{
  int i,j;
  float *a, *b, *c;
  int n = atoi(argv[1]);

  a = (float *) malloc(n * n * sizeof(float));
  b = (float *) malloc(n * n * sizeof(float));
  c = (float *) malloc(n * n * sizeof(float));

  #pragma omp threadprivate(cte)
  #pragma omp parallel num_threads(4)
  {
  #pragma omp single copyprivate(cte)
  	cte = atoi(argv[2]);
  #pragma omp for
  	for (i = 0; i < n * n; i++) {
     	a[i] = i + cte;
     	b[i] = i + cte + 1;
  	}
  }
  if (n < 10){ //Para comprobaciones
  	printf("matriz a\n");
  	ImprimirMatriz(a,n);
  	printf("matriz b\n");
  	ImprimirMatriz(b,n);
  }

  #pragma omp threadprivate(contador)
  contador = 0; // Inicialmente contador de iteraciones realizadas por hilo = 0

  #pragma omp parallel copyin(contador) num_threads(4)
  {
    #pragma omp for schedule(runtime)
      for (i = 0; i < n; i++) {
        contador++;
        for (j = 0; j < n; j++)
          c[i * n + j] = a[i * n + j] + b[i * n + j];
      }
      printf("1) El hilo %d ha realizado %d iteraciones\n", omp_get_thread_num(), contador);
  }

  printf("\n");

  if (n < 10){ //Para comprobaciones
  	printf("C despues de suma:\n");
  	ImprimirMatriz(c,n);
  }

  #pragma omp parallel num_threads(4)
  {
    #pragma omp for schedule(runtime)
        for (i = 0; i < n; i++) {
          contador++;
          for (j = 0; j < n; j++)
            c[i * n + j] += 2.0;
        }
     printf("2) El hilo %d ha realizado %d iteraciones\n", omp_get_thread_num(),contador);
  }

  printf("\n");

  if (n < 10){ //Para comprobaciones
          printf("C final:\n");
          ImprimirMatriz(c,n);
  }

  #pragma omp parallel
  {
  	printf ("3) Hilo %d, ha realizado %d iteraciones\n", omp_get_thread_num(),contador);
  }

}
