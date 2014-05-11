#include "camera.h"

void toGrayScale(unsigned char ***matriz, camera *cam){
	int i, j, r, g, b;
	float grayLevel;
	for(i = 0; i < cam->altura; i++)
	{
		for(j = 0; j < cam->largura; j++)
		{			
			//Gray = (Red * 0.2126 + Green * 0.7152 + Blue * 0.0722)
			grayLevel = ((float)cam->quadro[i][j][0]*0.2126 + 
						 (float)cam->quadro[i][j][1]*0.7152 + 
						 (float)cam->quadro[i][j][3]*0.0722);

			matriz[i][j][0] = grayLevel;
			matriz[i][j][1] = grayLevel;
			matriz[i][j][2] = grayLevel;
		}
	}	
}

void to_grey_scale(unsigned char ***matriz, camera *cam) {	
	int i, j, r, g, b, gscale;
	
	for(i = 0; i < cam->altura; i++) {
		for(j = 0; j < cam->largura; j++) {
	    	r = matriz[i][j][0];
	    	g = matriz[i][j][1];
	    	b = matriz[i][j][2];

	    	gscale = (r + g + b) / 3;
	    	matriz[i][j][0] = gscale;
	    	matriz[i][j][1] = gscale;
	    	matriz[i][j][2] = gscale;
		}
	}	
}

void copiaMatriz(unsigned char ***matriz, unsigned char ***alvo, camera *cam)
{
	int i, j;
	for(i = 0; i < cam->altura; i++)
	{
		for(j = 0; j < cam->largura; j++)
		{
			alvo[i][j][0] = matriz[i][j][0];
			alvo[i][j][1] = matriz[i][j][1];
			alvo[i][j][2] = matriz[i][j][2];
		}
	}
}


//TODO: Corrigir essa função pois ela está fazendo o contrário do que deveria
void binarizacao(unsigned char ***matriz, camera *cam, int threshold)
{
	int i,j;
	for(i = 0; i < cam->altura; i++){
		for(j = 0; j < cam->largura; j++){
			if(matriz[i][j][0] > threshold){
				matriz[i][j][0] = 255;
				matriz[i][j][1] = 255;
				matriz[i][j][2] = 255;
			}
			else{
				matriz[i][j][0] = 0;
				matriz[i][j][1] = 0;
				matriz[i][j][2] = 0;
			}
		}
	}
}

void binarize(unsigned char ***matriz, camera *cam, int threshold) {	
	int i,j;

	for(i = 0; i < cam->altura; i++) {
		for(j = 0; j < cam->largura; j++) {
			matriz[i][j][0] = (matriz[i][j][0] > threshold) ? 255 : 0;
			matriz[i][j][1] = (matriz[i][j][1] > threshold) ? 255 : 0;
			matriz[i][j][2] = (matriz[i][j][2] > threshold) ? 255 : 0;
		}
	}
}

void euclidian_distance(unsigned char ***frame_atual, unsigned char ***frame_anterior, camera *cam, int threshold) {
	int i, j;
	unsigned char r, g, b;
	for(i = 0; i < cam->altura; i++) {
		for(j = 0; j < cam->largura; j++) {
			r = frame_atual[i][j][0];
			g = frame_atual[i][j][1];
			b = frame_atual[i][j][2];

			r -= frame_anterior[i][j][0];
			g -= frame_anterior[i][j][1];
			b -= frame_anterior[i][j][2];

			r *= r;
			g *= g;
			b *= b;

			r = r + g + b;
			threshold *= threshold;
			
			frame_atual[i][j][0] = (r > threshold) ? 255 : 0;
			frame_atual[i][j][1] = (r > threshold) ? 255 : 0;
			frame_atual[i][j][2] = (r > threshold) ? 255 : 0;
		}
	}
}

//TODO: a funcao estava com erro e eu mudei para ela funcionar apenas para imagens em grayscale. Mudar para imagens comuns
//ou passar uma flag para a função informando que tipo de imagem será trabalhada
void dist_euclid(unsigned char ***frameAtual, unsigned char ***frameAnterior, unsigned char ***alvo, camera *cam, int threshold)
{
	int i, j;
	unsigned char r, g, b;
	for(i = 0; i < cam->altura; i++)
	{
		for(j = 0; j < cam->largura; j++)
		{
			r = frameAtual[i][j][0];
			g = frameAtual[i][j][1];
			b = frameAtual[i][j][2];

			r -= frameAnterior[i][j][0];
			g -= frameAnterior[i][j][1];
			b -= frameAnterior[i][j][2];

			r *= r;
			g *= g;
			b *= b;

			r = r + g + b;
			
			if (r > (threshold * threshold)) {
				alvo[i][j][0] = 255;
				alvo[i][j][1] = 255;
				alvo[i][j][2] = 255;
			} else {	    				
				alvo[i][j][0] = 0;
				alvo[i][j][1] = 0;
				alvo[i][j][2] = 0;
			}
			
			// r = frameAtual[i][j][0] - frameAnterior[i][j][0];
			
			/*
			if(r < 0) {
				r = -r;
			}

			if(r > threshold)
			{
				alvo[i][j][0] = 255;
				alvo[i][j][1] = 255;
				alvo[i][j][2] = 255;
			}
			else
			{
				alvo[i][j][0] = 0;
				alvo[i][j][1] = 0;
				alvo[i][j][2] = 0;
			}	
			//*/		
		}
	}
}

void sobel(unsigned char ***matriz, camera *cam, int threshold)
{
	unsigned char ***alvo = camera_aloca_matriz(cam);
	int i, j;
	int somaI = 0, somaJ = 0;
	//toGrayScale(matriz, cam);
	for(i = 1; i < cam->altura-1; i++)
	{
		for(j = 1; j < cam->largura-1; j++)
		{
			somaJ = ((-1*matriz[i-1][j-1][0]) +
					(matriz[i-1][j+1][0]) +
					(-2*matriz[i][j-1][0]) +
					(2*matriz[i][j+1][0]) +
					(-1*matriz[i+1][j-1][0]) +
					(matriz[i+1][j+1][0]));

			somaI = ((matriz[i-1][j-1][0])+
					(-1*matriz[i+1][j-1][0]) +
					(2*matriz[i-1][j][0]) +
					(-2*matriz[i+1][j][0]) + 
					(matriz[i-1][j+1][0]) + 
					(-1*matriz[i+1][j+1][0]));

			if(somaJ < 0)
				somaJ = -somaJ;

			if(somaI < 0)
				somaI = -somaI;

			if(somaI < threshold){
				somaI = 0;
			}

			if(somaJ < threshold){
				somaJ = 0;
			}

			alvo[i][j][0] = somaJ+somaI;
			alvo[i][j][1] = somaJ+somaI;
			alvo[i][j][2] = somaJ+somaI;
			//printf("Teste\n");
		}
	}
	copiaMatriz(alvo, matriz, cam);
	camera_libera_matriz(cam, alvo);
}

void gauss_filter(unsigned char ***matriz, camera *cam, bool colored)
{
	unsigned char ***alvo = camera_aloca_matriz(cam);
	copiaMatriz(matriz, alvo, cam);
	int valor = 0;
	int i, j, k;

	if(colored == false)
	{
		for(i = 2; i < cam->altura - 2; i++)
		{
			for(j = 2; j < cam->largura - 2; j++)
			{
				valor = (2*matriz[i-2][j-2][0] +  4*matriz[i-2][j-1][0] +  5*matriz[i-2][j][0] +  4*matriz[i-2][j+1][0] + 2*matriz[i-2][j+2][0] +
						 4*matriz[i-1][j-2][0] +  9*matriz[i-1][j-1][0] + 12*matriz[i-1][j][0] +  9*matriz[i-1][j+1][0] + 4*matriz[i-1][j+2][0] +
						 5*matriz[i][j-2][0]   + 12*matriz[i][j-1][0]   + 15*matriz[i][j][0]   + 12*matriz[i][j+1][0] +   5*matriz[i][j+2][0] +
						 4*matriz[i+1][j-2][0] +  9*matriz[i+1][j-1][0] + 12*matriz[i+1][j][0] +  9*matriz[i+1][j+1][0] + 4*matriz[i+1][j+2][0] +
					 	 2*matriz[i+2][j-2][0] +  4*matriz[i+2][j-1][0] +  5*matriz[i+2][j][0] +  4*matriz[i+2][j+1][0] + 2*matriz[i+2][j+2][0]) / 159;

				alvo[i][j][0] = valor;
				alvo[i][j][1] = valor;
				alvo[i][j][2] = valor;
			}			
		}
	}

	if(colored == true)
	{
		for(i = 2; i < cam->altura - 2; i++)
		{
			for(j = 2; j < cam->largura - 2; j++)
			{
				for(k = 0; k < 3; k++)
				{
					valor = (2*matriz[i-2][j-2][k] +  4*matriz[i-2][j-1][k] +  5*matriz[i-2][j][k] +  4*matriz[i-2][j+1][k] + 2*matriz[i-2][j+2][k] +
							 4*matriz[i-1][j-2][k] +  9*matriz[i-1][j-1][k] + 12*matriz[i-1][j][k] +  9*matriz[i-1][j+1][k] + 4*matriz[i-1][j+2][k] +
							 5*matriz[i][j-2][k]   + 12*matriz[i][j-1][k]   + 15*matriz[i][j][k]   + 12*matriz[i][j+1][k] +   5*matriz[i][j+2][k] +
							 4*matriz[i+1][j-2][k] +  9*matriz[i+1][j-1][k] + 12*matriz[i+1][j][k] +  9*matriz[i+1][j+1][k] + 4*matriz[i+1][j+2][k] +
						 	 2*matriz[i+2][j-2][k] +  4*matriz[i+2][j-1][k] +  5*matriz[i+2][j][k] +  4*matriz[i+2][j+1][k] + 2*matriz[i+2][j+2][k]) / 159;

					alvo[i][j][k] = valor;
				}
			}			
		}
	}
	

	copiaMatriz(alvo, matriz, cam);
	camera_libera_matriz(cam, alvo);
}