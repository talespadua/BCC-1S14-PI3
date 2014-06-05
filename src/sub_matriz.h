#ifndef _SUB_MATRIZ_H_
#define _SUB_MATRIZ_H_

#include "camera.h"

typedef struct {
	unsigned char ***matriz;
	int altura, largura;
} sub_matriz;

sub_matriz *sm_aloca(int altura, int largura);
sub_matriz *sm_aloca_por_matriz(unsigned char ***cam, int x_inicio, int y_inicio, int x_fim, int y_fim);
void sm_finaliza(sub_matriz *sm);

/* copia de uma sub_matriz atual para uma sub_matriz alvo */
void sm_sub_matriz_copy(sub_matriz *atual, sub_matriz *alvo);

/* sub_matriz alvo, matriz original, inicio da largura da matriz original, inicio da altura da matriz original */
void sm_matriz_copy(sub_matriz *alvo, unsigned char ***matriz, int x_inicio, int y_inicio);

#endif