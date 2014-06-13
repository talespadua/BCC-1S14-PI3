#include "init.h"



void erro(char *mensagem) {
	fputs(mensagem, stderr);

	exit(EXIT_FAILURE);
}

float maximum(float x, float y, float z) {
	float max = x; /* assume x is the largest */

	if (y > max) { /* if y is larger than max, assign y to max */
		max = y;
	} /* end if */

	if (z > max) { /* if z is larger than max, assign z to max */
		max = z;
	} /* end if */

	return max; /* max is the largest value */
} 

float minimum(float x, float y, float z) {
	float max = x; /* assume x is the largest */

	if (y < max) { /* if y is larger than max, assign y to max */
		max = y;
	} /* end if */

	if (z < max) { /* if z is larger than max, assign z to max */
		max = z;
	} /* end if */

	return max; /* max is the largest value */
} 
void RGBtoHSV(int r1 , int g1 , int b1 , float *h , float *s , float *v) 
{ 
	float min, max, delta; 
	float r,g,b;

	r = (float)r1 / 255;
	g = (float)g1 / 255;
	b = (float)b1 / 255;

	max = maximum(r , g ,b);
	min = minimum(r ,g ,b);

	
	if (max == r && g >= b)
	{
		*h = 60 * ((g - b) / (max - min)) + 0 ; 
	}

	if (max == r && g < b)
	{
		*h = 60 * ((g - b) / (max - min)) + 360; 
	}

	if (max == g)
	{
		*h = 60 * ((b - r) / (max - min)) + 120; 
	}

	if (max == b)
	{
		*h = 60 * ((r - g) / (max - min)) + 240; 
	}

	
	*s = ((max - min ) / max);
	*v = max;
	
}


int main()
{
	//INICIALIZAR ALLEGRO
	inicializar();

	al_start_timer(timer);

	int desenhar = 0;
	int terminar = 0;
	int countSegundo = 1;

	int sair = 1;

	//GAME LOOP
	while(sair)
	{
		//RECEBER EVENTOS

		ALLEGRO_EVENT ev;
		al_wait_for_event(fila_eventos, &ev);

		switch(ev.type) {
			case ALLEGRO_EVENT_TIMER:
			desenhar = 1;
			countSegundo++;
			break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			terminar = 1;
			break;
			default:
			printf("evento desconhecido\n");
		}

		if(terminar)
			break;

		if(desenhar && al_is_event_queue_empty(fila_eventos)) 
		{

			desenhar = 0;
			camera_atualiza(cam);

      /**********/

			float cy = 0;
			float cx = 0;
			int cn = 0;
			float h;
			float s;
			float v;


			int verde = 0;
			int vermelho = 0;
			int azul = 0;
			int amarelo = 0;

			
			for(int y = 0; y < altura; y++)
				for(int x = 0; x < largura; x++) {
					int r = cam->quadro[y][x][0];
					int g = cam->quadro[y][x][1];
					int b = cam->quadro[y][x][2];

					

					int r1 = (int)r;
					int g1 = (int)g;
					int b1 = (int)b;

					RGBtoHSV(r1 ,g1 ,b1 , &h , &s , &v);

					matriz[y][x][0] = 0;
						matriz[y][x][1] = 0;
						matriz[y][x][2] = 0;

					//vermelho legal
					if( (h >= 350 || h <= 10) && (s > 0.6) && (v > 0.4)   ) 
					{
						
						vermelho++;
						matriz[y][x][0] = 255;
						matriz[y][x][1] = 0;
						matriz[y][x][2] = 0;
					}


					//verde maneiro
					if( (h >= 64 && h <= 150) && (s > 0.15) && (v > 0.15 )   ) 
					{
						
						verde++;
						matriz[y][x][0] = 0;
						matriz[y][x][1] = 255;
						matriz[y][x][2] = 0;
					}


					if( (h >= 180 && h <= 255) && (s > 0.15) && (v > 0.15 )   ) 
					{
						azul++;
						matriz[y][x][0] = 0;
						matriz[y][x][1] = 0;
						matriz[y][x][2] = 255;
					}


					 //if(  (h >= 20 && h <= 45)   && (s > 0.65) && (v > 0.6 ) ) 
					 //if(  (h >= 20 && h <= 45)   && (s > 0.65) && (v > 0.6 ) ) 
					 if(  (h >= 30 && h <= 45)   && (s > 0.5) && (v > 0.55 ) ) 
					 {
					 	amarelo++;
					 	matriz[y][x][0] = 255;
						matriz[y][x][1] = 255;
						matriz[y][x][2] = 0;
					 
					 }
					 
				}
				camera_copia(cam, cam->quadro, esquerda);

				int tam = 5000;
				
				if (verde > tam || vermelho > tam || azul > tam || amarelo > tam )
				{
			
					if (verde > tam)
					{
						printf("verde\n");
					}

					if (azul > tam)
					{
						printf("azul\n");
					}

					if (vermelho >tam)
					{
						printf("vermelho\n");
					}

					if (amarelo >tam)
					{
						printf("amarelo\n");
					}

					
				}
				else
				{
					//printf("nada\n");
				}
	
				camera_copia(cam, matriz, direita);
				al_flip_display();
			}

			if (countSegundo == 60)
			{
				printf("um segundo\n");
				countSegundo = 1;
			}

		}

	//SAIR DO JOGO 
		al_destroy_display(janela);
		al_destroy_event_queue(fila_eventos);

		return 0;
	}