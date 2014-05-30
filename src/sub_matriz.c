#include "sub_matriz.h"

sub_matriz *sm_aloca(int altura, int largura) {

}

sub_matriz *sm_aloca_por_camera(camera *cam, int x_inicio, int y_inicio, int x_fim, int y_fim) {

}

void sm_finaliza(sub_matriz *cam) {
	int x, y;

	for(int y = 0; y < cam->altura; y++) {
		for(int x = 0; x < cam->largura; x++) {
			free(matriz[y][x]);
		}

		free(matriz[y]);
	}

	free(matriz);
}


void sm_sub_matrix_copy (sub_matriz *atual, sub_matriz *alvo) {
	int i, j;

	for (i = 0; i < atual->altura; i++) {
		for (j = 0; j < atual->largura; j++) {
			alvo->matriz[i][i][0] = atual->matriz[i][j][0];		
			alvo->matriz[i][i][1] = atual->matriz[i][j][1];
			alvo->matriz[i][i][2] = atual->matriz[i][j][2];
		}
	}
}

void sm_matrix_copy(sub_matriz *alvo, unsigned char ***matriz, int x_inicio, int y_inicio) {
	int i, j;

	for (i = 0; i < atual->altura; i++) {
		for (j = 0; j < atual->largura; j++) {
			alvo->matriz[i][i][0] = matriz[i + y_inicio][j + x_inicio][0];		
			alvo->matriz[i][i][1] = matriz[i + y_inicio][j + x_inicio][1];
			alvo->matriz[i][i][2] = matriz[i + y_inicio][j + x_inicio][2];
		}
	}
}