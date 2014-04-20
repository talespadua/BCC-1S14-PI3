#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "camera.h"

/* Cópia da matriz de tamanho cam->largura x cam->altura em alvo. */
void matrix_copy(unsigned char ***matriz, unsigned char ***alvo, camera *cam);
/* Escala de cinza em matriz de tamanho cam->largura x cam->altura. */
void to_grey_scale(unsigned char ***matriz, camera *cam);
/* Binariza com dado threshold matriz de tamanho cam->largura x cam->altura. */
void binarize(unsigned char ***matriz, camera *cam, int threshold);
/* Distância euclidiana com dado threshold entre frame_atual e frame_anterior. */
void euclidian_distance(unsigned char ***frame_atual, unsigned char ***frame_anterior, camera *cam, int threshold);
/* Filtro de Sobel com dado threshold em matriz. Aviso: entrega a matriz de entrada. */
void sobel_operator(unsigned char ***matriz, camera *cam, int threshold);

#endif