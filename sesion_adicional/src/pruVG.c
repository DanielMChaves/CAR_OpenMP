/*
 * Compile me with:
 * (make --see Makefile--)
 */
 
// #include <gtk/gtk.h>

//#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "img_ng.h"

// Fichero de trabajo
char * FichImagen1;
// Modo silencioso
int    Silent;

static void
usage(void)
{
  (void) fprintf(stderr, "usage: %s [-h] [-s] -f image_file\n", "pruVG");
  exit(1);
}

static void
printhelp(void)
{
  (void) fprintf(stderr, "usage: %s [-h] [-s] -f image_file\n", "pruVG");
  (void) fprintf(stderr, "-h: this help\n");
  (void) fprintf(stderr, "-s: silent mode\n");
  (void) fprintf(stderr, "-f file: image to be processed\n");
  (void) fprintf(stderr, "pruVG: basic image processing + Valgrind\n");
  exit(0);
}

int
main( int    argc,
      char **argv )
{
  int ch, res;
  struct stat sb;

    /* Tratar opciones de llamada */
    FichImagen1 = NULL;
    Silent = 0;
    while ((ch = getopt(argc, argv, "hsf:")) != -1)
      switch (ch)
	{
	case 'h':
	  printhelp();
	  break;
	case 'f':
	  FichImagen1 = optarg;
	  break;
	case 's':
	  Silent = 1;
	  break;
	case '?':
	default:
	  usage();
	}

    if (FichImagen1 != NULL) {
      if (Silent)
	fprintf(stdout, "%s: ", FichImagen1);
      else
	fprintf(stderr, "Fichero con imagen inicial: %s\n", FichImagen1);

      if (stat(FichImagen1, &sb) != -1)
	leeImagenOriginal_ng(FichImagen1);
      else {
	fprintf(stderr, "El fichero %s no existe/no se puede leer\n", FichImagen1);
	return -1;
      }

      res=ejecutaPPAL();

      if (!Silent)
	printf("Resultado (nFilt)=%d\n", res);
    } else
	printhelp();

    return( 0 );
}
