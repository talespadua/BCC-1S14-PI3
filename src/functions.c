// #include "camera.h"
// #include "functions.h"

// void matrix_copy(unsigned char ***matriz, unsigned char ***alvo, camera *cam) {
// 	int i, j;

// 	for(i = 0; i < cam->altura; i++) {
// 		for(j = 0; j < cam->largura; j++) {
// 			alvo[i][j][0] = matriz[i][j][0];
// 			alvo[i][j][1] = matriz[i][j][1];
// 			alvo[i][j][2] = matriz[i][j][2];
// 		}
// 	}
// }

// void to_grey_scale(unsigned char ***matriz, camera *cam) {	
// 	int i, j, r, g, b, gscale;
	
// 	for(i = 0; i < cam->altura; i++) {
// 		for(j = 0; j < cam->largura; j++) {
// 	    	r = matriz[i][j][0];
// 	    	g = matriz[i][j][1];
// 	    	b = matriz[i][j][2];

// 	    	gscale = (r + g + b) / 3;
// 	    	matriz[i][j][0] = gscale;
// 	    	matriz[i][j][1] = gscale;
// 	    	matriz[i][j][2] = gscale;
// 		}
// 	}	
// }

// void binarize(unsigned char ***matriz, camera *cam, int threshold) {	
// 	int i,j;

// 	for(i = 0; i < cam->altura; i++) {
// 		for(j = 0; j < cam->largura; j++) {
// 			matriz[i][j][0] = (matriz[i][j][0] > threshold) ? 255 : 0;
// 			matriz[i][j][1] = (matriz[i][j][1] > threshold) ? 255 : 0;
// 			matriz[i][j][2] = (matriz[i][j][2] > threshold) ? 255 : 0;
// 		}
// 	}
// }

// void euclidian_distance(unsigned char ***frame_atual, unsigned char ***frame_anterior, camera *cam, int threshold) {
// 	int i, j;
// 	unsigned char r, g, b;

// 	for(i = 0; i < cam->altura; i++) {
// 		for(j = 0; j < cam->largura; j++) {
// 			r = frame_atual[i][j][0];
// 			g = frame_atual[i][j][1];
// 			b = frame_atual[i][j][2];

// 			// Tira diferença de frames.
// 			r -= frame_anterior[i][j][0];
// 			g -= frame_anterior[i][j][1];
// 			b -= frame_anterior[i][j][2];

// 			// Eleva ao quadrado.
// 			r *= r;
// 			g *= g;
// 			b *= b;

// 			r = r + g + b;

// 			// Eleva o threshold ao quadrado para não precisar tirar raiz.
// 			threshold *= threshold;
			
// 			// Compara com o threshold.
// 			frame_atual[i][j][0] = (r > threshold) ? 255 : 0;
// 			frame_atual[i][j][1] = (r > threshold) ? 255 : 0;
// 			frame_atual[i][j][2] = (r > threshold) ? 255 : 0;
// 		}
// 	}
// }

// void sobel_operator(unsigned char ***matriz, camera *cam, int threshold) {
// 	int i, j;
// 	int soma_i = 0, soma_j = 0;
// 	unsigned char ***alvo;
	
// 	for(i = 1; i < cam->altura-1; i++) {
// 		for(j = 1; j < cam->largura-1; j++) {
// 			soma_j = ((-1*matriz[i-1][j-1][0]) +
// 					(matriz[i-1][j+1][0]) +
// 					(-2*matriz[i][j-1][0]) +
// 					(2*matriz[i][j+1][0]) +
// 					(-1*matriz[i+1][j-1][0]) +
// 					(matriz[i+1][j+1][0]));

// 			soma_i = ((matriz[i-1][j-1][0])+
// 					(-1*matriz[i+1][j-1][0]) +
// 					(2*matriz[i-1][j][0]) +
// 					(-2*matriz[i+1][j][0]) + 
// 					(matriz[i-1][j+1][0]) + 
// 					(-1*matriz[i+1][j+1][0]));

// 			if (soma_j < 0) {			
// 				soma_j = -soma_j;	
// 			}

// 			if (soma_i < 0) {
// 				soma_i = -soma_i;				
// 			}

// 			if (soma_i < threshold) {
// 				soma_i = 0;
// 			}

// 			if(soma_j < threshold) {
// 				soma_j = 0;
// 			}

// 			alvo[i][j][0] = soma_j + soma_i;
// 			alvo[i][j][1] = soma_j + soma_i;
// 			alvo[i][j][2] = soma_j + soma_i;
// 			//printf("Teste\n");
// 		}
// 	}

// 	matrix_copy(alvo, matriz, cam);
// }