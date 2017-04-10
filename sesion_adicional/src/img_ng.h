#ifndef _IMG_NG_H_
#define _IMG_NG_H_

typedef unsigned char uchar;

typedef struct {
  uchar *imagen;
  int height, width;
  int maxHeight, maxWidth;
  int offWidth, offImg;
  int modificada; // boolean
  int rowbytes, channels;
} tImagen ;

void leeImagenOriginal_ng(char *nomImagen);
void escribeImagenOriginal_ng(tImagen * Im, char *nomImagen);

#if defined (COD2016)
struct mFiltro {
  int K;
  int nucleo[9];
};
#elif defined (COD2015)
struct mFiltro {
  int K;
  int C;
  int B;
};
#endif
typedef struct mFiltro mFiltro_t ;

int ejecutaPPAL(void);
int filtRec(tImagen *im_in, mFiltro_t *MF, int nCambios, int nFiltrados);
void Filtro(tImagen *im_i, tImagen *im_o, mFiltro_t *MF);
uchar FilPixel(tImagen *im_ima, int i, int j, mFiltro_t *MF);
void SubMatriz(tImagen *im, uchar *subimg, int i, int j);
uchar valorPixel(uchar *s_img, mFiltro_t *MF);
int Comp(tImagen *i1, tImagen *i2);

#endif /* _IMG_NG_H_ */
