// FROM:
// LibPNG example
// A.Greensted
// http://www.labbookpages.co.uk
// Version 2.0

#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <png.h>

#include "write_png.h"

// This takes the float value 'val', converts it to red, green & blue values, then 
// sets those values into the image memory buffer location pointed to by 'ptr'
inline void setRGB(png_byte *ptr, float val);

inline void setRGB(png_byte *ptr, float val)
{
	int v = (int)(val * 767);
	if (v < 0) v = 0;
	if (v > 767) v = 767;
	int offset = v % 256;

	if (v<256) {
		ptr[0] = 0; ptr[1] = 0; ptr[2] = offset;
	}
	else if (v<512) {
		ptr[0] = 0; ptr[1] = offset; ptr[2] = 255-offset;
	}
	else {
		ptr[0] = offset; ptr[1] = 255-offset; ptr[2] = 0;
	}
}


int writeImage(char* filename, int width, int height, int channels, uchar *buffer)
{
	int code = 0;
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;
	int y;
	
	//	fprintf(stdout, "channels=%d\n", channels);

	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error during png creation\n");
		code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	if (channels == 3) {
	  // Write header (8 bit colour depth - RGB)
	  png_set_IHDR(png_ptr, info_ptr, width, height,
		       8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
		       PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	} else if (channels == 4) {
	  // Write header (8 bit colour depth - RGB + ALPHA)
	  png_set_IHDR(png_ptr, info_ptr, width, height,
		       8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
		       PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	} else if (channels == 1) {
	  // Write header (8 bit colour depth - GRAY)
	  png_set_IHDR(png_ptr, info_ptr, width, height,
		       8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
		       PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	} else {
	  fprintf(stderr, "Error assigning colour depth (png) \n");
	  code = 1;
	  goto finalise;
	}
	
	png_write_info(png_ptr, info_ptr);
	// Write image data
	for (y=0 ; y<height ; y++) {
		row = buffer+channels*y*width;
		png_write_row(png_ptr, row);
	}
	
	// End write
	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	//	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (info_ptr != NULL) free(info_ptr);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);

	return code;
}
