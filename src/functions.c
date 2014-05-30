#include "functions.h"
#include "camera.h"





void sm_grey_scale(sub_matriz *cam) {	
	int i, j;
	unsigned char r, g, b, grey_scale;
	
	for(i = 0; i < cam->altura; i++) {
		for(j = 0; j < cam->largura; j++) {
	    	r = cam->matriz[i][j][0];
	    	g = cam->matriz[i][j][1];
	    	b = cam->matriz[i][j][2];

	    	// grey scale = media aritimetica das tres componentes de cor
	    	grey_scale = (r + g + b) / 3;
	    	cam->matriz[i][j][0] = grey_scale;
	    	cam->matriz[i][j][1] = grey_scale;
	    	cam->matriz[i][j][2] = grey_scale;
		}
	}	
}

void sm_binarize(sub_matriz *cam, int threshold) {	
	int i,j;

	for(i = 0; i < cam->altura; i++) {
		for(j = 0; j < cam->largura; j++) {
			cam->matriz[i][j][0] = (cam->matriz[i][j][0] > threshold) ? 255 : 0;
			cam->matriz[i][j][1] = (cam->matriz[i][j][1] > threshold) ? 255 : 0;
			cam->matriz[i][j][2] = (cam->matriz[i][j][2] > threshold) ? 255 : 0;
		}
	}
}

void sm_euclidian_distance(sub_matriz *atual, sub_matriz *anterior, int threshold) {
	int i, j;
	unsigned char r, g, b;

	for(i = 0; i < atual->altura; i++) {
		for(j = 0; j < atual->largura; j++) {
			// Pega os pontos atuais
			r = atual->matriz[i][j][0];
			g = atual->matriz[i][j][1];
			b = atual->matriz[i][j][2];

			// Tira a diferenca com os pontos anteriores
			r -= anterior->matriz[i][j][0];
			g -= anterior->matriz[i][j][1];
			b -= anterior->matriz[i][j][2];

			// eleva a diferenca ao quadrado
			r *= r;
			g *= g;
			b *= b;

			// soma a diferenca
			r = r + g + b;
			// eleva a limitrofe ao quadrado tambem para nao ter que tirar raizes
			threshold *= threshold;
			
			// aplica a diferenca de acordo como o ponto se comporta em relacao a limitrofe
			atual->matriz[i][j][0] = (r > threshold) ? 255 : 0;
			atual->matriz[i][j][1] = (r > threshold) ? 255 : 0;
			atual->matriz[i][j][2] = (r > threshold) ? 255 : 0;
		}
	}
}

void sm_sobel(sub_matriz *atual, sub_matriz *alvo, int threshold) {
	int i, j;
	int soma, soma_i = 0, soma_j = 0;
	//toGrayScale(matriz, cam);

	for(i = 1; i < cam->altura-1; i++) {
		for(j = 1; j < cam->largura-1; j++) {
			soma_j = (	(-1 * atual->matriz[i-1][j-1][0]) +
						(atual->matriz[i-1][j+1][0]) +
						(-2 * atual->matriz[i][j-1][0]) +
						(2 * atual->matriz[i][j+1][0]) +
						(-1 * atual->matriz[i+1][j-1][0]) +
						(atual->matriz[i+1][j+1][0]));

			soma_i = (	(atual->matriz[i-1][j-1][0])+
						(-1 * atual->matriz[i+1][j-1][0]) +
						(2 * atual->matriz[i-1][j][0]) +
						(-2 * atual->matriz[i+1][j][0]) + 
						(atual->matriz[i-1][j+1][0]) + 
						(-1 * atual->matriz[i+1][j+1][0]));

			if (soma_j < 0)
				soma_j = - soma_j;

			if (soma_i < 0)
				soma_i = -soma_i;

			if (soma_i < threshold)
				soma_i = 0;
			
			if (soma_j < threshold)
				soma_j = 0;			

			soma = soma_j + soma_i;
			alvo->matriz[i][j][0] = soma;
			alvo->matriz[i][j][1] = soma;
			alvo->matriz[i][j][2] = soma;
		}
	}
}