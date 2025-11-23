//Craciun Mihai Alexandru 313CA
#ifndef FUNCTII_H
#define FUNCTII_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int r;
	int g;
	int b;
} rgb;

typedef struct {
	int width;	 // width
	int height;	 // height
	rgb **data;	 // matrice
	char tip[3]; // tip
	int maxim;
} image;

int load_file(char *name, FILE **file);
int save_file(char *name, FILE **file, int is_ascii);
void aloc_image(image *my_image);
void free_image(image *my_image);
void read_image(image *my_image, FILE **file);
void read_imagemetadata(image *my_image, FILE **file, char *name);
void save_image(image *my_image, FILE **file, int is_ascii);
void apply(image *my_image, char *apply_op, int x1, int y1, int x2, int y2);
void select_region(image *my_image, int *x1, int *y1, int *x2, int *y2);
void crop(image *my_image, int *x1, int *y1, int *x2, int *y2);
void histogram(image *my_image, int x1, int y1, int x2, int y2);
void equalize(image *my_image);
void rotate(image *my_image, int *x1, int *y1, int *x2, int *y2);
void clear_input_buffer(void);

#endif
