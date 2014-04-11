#ifndef FUNC_H
#define FUNC_H

#include "camera.h"

void toGrayScale(unsigned char ***matriz, camera *cam);
void copiaMatriz(unsigned char ***matriz, unsigned char ***alvo, camera *cam);
void binarizacao(unsigned char ***matriz, camera *cam, int threshold);
void dist_euclid(unsigned char ***frameAtual, unsigned char ***frameAnterior, unsigned char ***alvo, camera *cam, int threshold);
void sobel(unsigned char ***matriz, camera *cam, int threshold);

#endif