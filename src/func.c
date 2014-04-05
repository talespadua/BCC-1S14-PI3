#include "camera.h"

void toGrayScale(unsigned char ***matriz, camera *cam){
	int i, j;
	unsigned char grayLevel;
	for(i = 0; i < cam->altura; i++)
	{
		for(j = 0; j < cam->largura; j++)
		{
			grayLevel = (cam->quadro[i][j][0] + cam->quadro[i][j][1] + cam->quadro[i][j][3])/3;
			matriz[i][j][0] = grayLevel;
			matriz[i][j][1] = grayLevel;
			matriz[i][j][2] = grayLevel;
		}
	}
}

void copiaMatriz(unsigned char ***matriz, camera *cam)
{
	int i, j;
	for(i = 0; i < cam->altura; i++)
	{
		for(j = 0; j < cam->largura; j++)
		{
			matriz[i][j][0] = cam->quadro[i][j][0];
			matriz[i][j][1] = cam->quadro[i][j][1];
			matriz[i][j][2] = cam->quadro[i][j][2];
		}
	}
}

