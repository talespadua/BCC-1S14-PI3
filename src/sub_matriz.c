#include "sub_matriz.h"

sub_matriz *sm_aloca(int altura, int largura) {
	int x, y;	
	sub_matriz *sm = malloc(sizeof(sub_matriz));

	sm->altura = altura;
	sm->largura = largura;

	sm->matriz = malloc(cam->altura * sizeof(unsigned char **));

	for(int y = 0; y < cam->altura; y++) {
    	sm->matriz[y] = malloc(cam->largura * sizeof(unsigned char *));

    	for(int x = 0; x < cam->largura; x++)
     		sm->matriz[y][x] = malloc(3 * sizeof(unsigned char));
  	}

  	return sm;
}

sub_matriz *sm_aloca_por_matriz(unsigned char ***cam, int x_inicio, int y_inicio, int x_fim, int y_fim) {
	// altura = y_fim - y_inicio; largura = x_fim - x_inicio;
	sub_matriz *sm = sm_aloca((y_fim - y_inicio), (x_fim - x_inicio));
	sm_matriz_copy(sm, cam, x_inicio, y_inicio);

	return sm;
}

void sm_finaliza(sub_matriz *sm) {
	int x, y;

	for(int y = 0; y < sm->altura; y++) {
		for(int x = 0; x < sm->largura; x++) {
			free(sm->matriz[y][x]);
		}

		free(sm->matriz[y]);
	}

	free(sm->matriz);

	free(sm);
}


void sm_sub_matriz_copy (sub_matriz *atual, sub_matriz *alvo) {
	int x, y;

	for (y = 0; y < atual->altura; y++) {
		for (x = 0; x < atual->largura; x++) {
			alvo->matriz[y][x][0] = atual->matriz[y][x][0];		
			alvo->matriz[y][x][1] = atual->matriz[y][x][1];
			alvo->matriz[y][x][2] = atual->matriz[y][x][2];
		}
	}
}

void sm_matriz_copy(sub_matriz *alvo, unsigned char ***matriz, int x_inicio, int y_inicio) {
	int x, y;

	for (y = 0; y < atual->altura; y++) {
		for (x = 0; x < atual->largura; x++) {
			alvo->matriz[y][x][0] = matriz[y + y_inicio][x + x_inicio][0];		
			alvo->matriz[y][x][1] = matriz[y + y_inicio][x + x_inicio][1];
			alvo->matriz[y][x][2] = matriz[y + y_inicio][x + x_inicio][2];
		}
	}
}