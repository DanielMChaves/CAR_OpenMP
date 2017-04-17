
# CC     = gcc
CC     = /opt/intel/bin/icc

# CFLAGS = -Wall -g -O0
CFLAGS = -qopenmp -Wall -g -O2
# CFLAGS = -Wall -g -O3 -fno-inline

LIBS   = -lm -lpng12 -lz

# Para dar acceso a las librerías compartidas de
# intel cuando se usa el compilador icc:
#    export LD_LIBRARY_PATH=/opt/intel/lib/intel64
#
# Para maximizar el espacio disponible en pila:
#    ulimit -s unlimited

PROG = pruVG
PROGo = pruVGo

OBJECTS  = $(PROG).o readpng.o write_png.o img_ng.o
OBJECTSo = $(PROG).o readpng.o write_png.o img_ngo.o

.PHONY: clean

.c.o:	
	$(CC) $(CFLAGS) -c $< -o $@

all: prueba1 prueba2 prueba3

prueba1:	prueba1.o
	$(CC) $(CFLAGS) $< -o $@

prueba2:	prueba2.o
	$(CC) $(CFLAGS) $< -o $@

prueba3:	prueba3.o
	$(CC) $(CFLAGS) $< -o $@

pruVG:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

pruVGo:	$(OBJECTSo)
	$(CC) $(CFLAGS) $(OBJECTSo) -o $@ $(LIBS)

readpng.o: readpng.c readpng.h img_ng.h

write_png.o: write_png.c write_png.h img_ng.h

img_ng.o: img_ng.c img_ng.h

clean:
	rm -f *.o $(PROG) $(PROGo) prueba1 prueba2 prueba3 *~
