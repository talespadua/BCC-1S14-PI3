#ifndef _SUB_MATRIZ_H_
#define _SUB_MATRIZ_H_

#include "camera.h"

typedef struct {
	unsigned char ***matriz;
	int altura, largura;
} sub_matriz;

sub_matriz *sm_aloca(int altura, int largura);
sub_matriz *sm_aloca_por_camera(camera *cam, int x_inicio, int y_inicio, int x_fim, int y_fim);
void sm_finaliza(sub_matriz *cam);

/* copia de uma sub_matriz atual para uma sub_matriz alvo*/
void sm_sub_matrix_copy(sub_matriz *atual, sub_matriz *alvo);

/* sub_matriz alvo, matriz que vai copiar, inicio da largura da matriz original, inicio da altura da matriz original */
void sm_matrix_copy(sub_matriz *alvo, unsigned char ***matriz, int x_inicio, int y_inicio);

#endif