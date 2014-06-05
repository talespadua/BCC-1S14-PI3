#include "sm_functions.h"

void sm_grey_scale(sub_matriz *cam) {	
	int x, y;
	unsigned char r, g, b, grey_scale;
	
	for(y = 0; y < cam->altura; y++) {
		for(x = 0; x < cam->largura; x++) {
	    	r = cam->matriz[y][x][0];
	    	g = cam->matriz[y][x][1];
	    	b = cam->matriz[y][x][2];

	    	// grey scale = media aritimetica das tres componentes de cor
	    	grey_scale = (r + g + b) / 3;
	    	cam->matriz[y][x][0] = grey_scale;
	    	cam->matriz[y][x][1] = grey_scale;
	    	cam->matriz[y][x][2] = grey_scale;
		}
	}	
}

void sm_binarize(sub_matriz *cam, int threshold) {	
	int x, y;

	for(y = 0; y < cam->altura; y++) {
		for(x = 0; x < cam->largura; x++) {
			cam->matriz[y][x][0] = (cam->matriz[y][x][0] > threshold) ? 255 : 0;
			cam->matriz[y][x][1] = (cam->matriz[y][x][1] > threshold) ? 255 : 0;
			cam->matriz[y][x][2] = (cam->matriz[y][x][2] > threshold) ? 255 : 0;
		}
	}
}

void sm_euclidian_distance(sub_matriz *atual, sub_matriz *anterior, int threshold) {
	int x, y;
	unsigned char r, g, b;

	for(y = 0; y < atual->altura; y++) {
		for(x = 0; x < atual->largura; x++) {
			// Pega os pontos atuais
			r = atual->matriz[y][x][0];
			g = atual->matriz[y][x][1];
			b = atual->matriz[y][x][2];

			// Tira a diferenca com os pontos anteriores
			r -= anterior->matriz[y][x][0];
			g -= anterior->matriz[y][x][1];
			b -= anterior->matriz[y][x][2];

			// eleva a diferenca ao quadrado
			r *= r;
			g *= g;
			b *= b;

			// soma a diferenca
			r = r + g + b;
			// eleva a limitrofe ao quadrado tambem para nao ter que tirar raizes
			threshold *= threshold;
			
			// aplica a diferenca de acordo como o ponto se comporta em relacao a limitrofe
			atual->matriz[y][x][0] = (r > threshold) ? 255 : 0;
			atual->matriz[y][x][1] = (r > threshold) ? 255 : 0;
			atual->matriz[y][x][2] = (r > threshold) ? 255 : 0;
		}
	}
}

void sm_sobel(sub_matriz *atual, sub_matriz *alvo, int threshold) {
	int x, y;
	int soma, soma_i = 0, soma_j = 0;

	for(y = 1; y < atual->altura-1; y++) {
		for(x = 1; x < atual->largura-1; x++) {
			soma_j = (	(-1 * atual->matriz[y-1][x-1][0]) +
						(atual->matriz[y-1][x+1][0]) +
						(-2 * atual->matriz[y][x-1][0]) +
						(2 * atual->matriz[y][x+1][0]) +
						(-1 * atual->matriz[y+1][x-1][0]) +
						(atual->matriz[y+1][x+1][0]));

			soma_i = (	(atual->matriz[y-1][x-1][0]) +
						(-1 * atual->matriz[y+1][x-1][0]) +
						(2 * atual->matriz[y-1][x][0]) +
						(-2 * atual->matriz[y+1][x][0]) + 
						(atual->matriz[y-1][x+1][0]) + 
						(-1 * atual->matriz[y+1][x+1][0]));

			if (soma_i < 0)
				soma_i = -soma_i;

			if (soma_j < 0)
				soma_j = -soma_j;

			if (soma_i < threshold)
				soma_i = 0;
			
			if (soma_j < threshold)
				soma_j = 0;			

			soma = soma_j + soma_i;
			alvo->matriz[y][x][0] = soma;
			alvo->matriz[y][x][1] = soma;
			alvo->matriz[y][x][2] = soma;
		}
	}
}