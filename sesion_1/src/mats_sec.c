/*** Probamos threadprivate, copyin y schedule             ***/
/****  Version secuencial                                  ***/
/** Argumentos: #filas_matriz cte_inicializacion_matrices  ***/

#include<stdio.h>
#include <omp.h>

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
int n= atoi(argv[1]);
int contador =0;

a = (float *) malloc(n * n * sizeof(float));
b = (float *) malloc(n * n * sizeof(float));
c = (float *) malloc(n * n * sizeof(float));

cte = atoi(argv[2]);
for (i=0; i<n*n; i++) {
  	a[i] = i+cte;
   	b[i] = i+cte+1;
}
if (n<10){ //Para comprobaciones
	printf("matriz a\n");
	ImprimirMatriz(a,n);
	printf("matriz b\n");
	ImprimirMatriz(b,n);
}

contador = 0; // Inicialmente contador de iteraciones realizadas por hilo = 0

for (i=0; i<n; i++) {
	contador++;
	for (j=0; j<n; j++)
	   c[i*n+j] = a[i*n+j]+b[i*n+j];
 }
 printf("1) El hilo %d ha realizado %d iteraciones\n", 0, contador);

 printf("\n");

if (n<10){ //Para comprobaciones
	printf("C despues de suma:\n");
	ImprimirMatriz(c,n);
}

for (i=0; i<n; i++) {
        contador++;
        for (j=0; j<n; j++)
           c[i*n+j] +=2.0;
}
 printf("2) El hilo %d ha realizado %d iteraciones\n", 0,contador);

printf("\n");

if (n<10){ //Para comprobaciones
        printf("C final:\n");
        ImprimirMatriz(c,n);
}

printf ("3) Hilo %d, ha realizado %d iteraciones\n", 0, contador);

}

