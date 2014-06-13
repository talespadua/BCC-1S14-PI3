#include "init.h"


void destacarAmarelo()
{
	cor_amarelo = al_map_rgb_f(1, 1, 0);
}

void destacarAzul()
{
	cor_azul = al_map_rgb_f(0, 0, 1);
}

void destacarVermelho()
{
	cor_vermelha = al_map_rgb_f(1, 0, 0);
}

void destacarVerde()
{
	cor_verde = al_map_rgb_f(0, 1, 0);
}



void escreverCor(int x)
{

	switch (x)
	{
		case 1:
		printf("verde\n");
		destacarVerde();
		al_play_sample(sample1, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;

		case 2:
		printf("vermelho\n");
		destacarVermelho();
		al_play_sample(sample2, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;

		case 3 :
		printf("azull\n");
		destacarAzul();
		al_play_sample(sample3, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;

		case 4 :
		printf("amarelo\n");
		destacarAmarelo();
		al_play_sample(sample4, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		break;

	}

	printf("passeu\n");
}

void coresOriginais()
{
	cor_verde = al_map_rgb_f(0, 0.35, 0);
	cor_vermelha = al_map_rgb_f(0.35, 0, 0);
	cor_azul = al_map_rgb_f(0, 0, 0.35);
	cor_amarelo = al_map_rgb_f(0.35, 0.35, 0);
}


void desenharQuadrado()
{
	al_draw_rectangle(100, 100, 100, 100, cor_verde, 1);
}


int RandomInteger( int low, int high)
{
	int k;
	double d;
	d = (double) rand( ) / ((double) RAND_MAX + 1);
	k = d * (high - low + 1);
	return low + k;
}

void Randomize( void)
{
	srand( time( NULL));
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
	float min, max; 
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

void desenharTela()
{
	//superiores
	al_draw_filled_rectangle(0, 0, largura /2 , 0 + altura / 2, cor_azul);
	al_draw_filled_rectangle( largura / 2 , 0, largura + largura , 0 + altura / 2, cor_vermelha);

	//inferiores
	al_draw_filled_rectangle(0, altura / 2 , largura / 2, 0 + altura, cor_amarelo);
	al_draw_filled_rectangle(largura / 2 , altura / 2, largura , 0 + altura, cor_verde);
}

sortearJogadas()
{

	for (int i = 0; i < 50; ++i)
	{
		jogadas[i] = RandomInteger(1, 4);
	}

}

void perder(int *teste)
{
	al_play_sample(peido, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
	al_rest(1.5);
	*teste = 2;
}

int main()
{
	//INICIALIZAR ALLEGRO
	inicializar();
	Randomize();
	al_play_sample(moeda, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);


	int contadorJogada = 0;

	sortearJogadas();

	al_start_timer(timer);

	//CONTROLE DE JOGO
	int desenhar = 0;
	int terminar = 0;
	int sair = 1;

	//CONTROLE DE VERIFICACAO
	int repeat = 0;
	int repeatVerifica = 0;
	int repeatConfere = 0;

	//CONTROLE DA RODADA
	int rodada = 1;

	//VARIAVEIS LEGAIS SEM DESCRICAO UTIL
	int countAzul = 1;
	int countAmarelo = 1;
	int countVermelho = 1;
	int countVerde = 1;


	int verde = 0;
	int vermelho = 0;
	int azul = 0;
	int amarelo = 0;

	float h;
	float s;
	float v;

	int telas = 0;
	 

	 int verLegal = 0;
	//GAME LOOP
	while(sair)
	{
		//RECEBER EVENTOS
		ALLEGRO_EVENT ev;
		al_wait_for_event(fila_eventos, &ev);

		switch(ev.type) {
			case ALLEGRO_EVENT_KEY_DOWN:
				  switch(ev.keyboard.keycode)
                {
                	case ALLEGRO_KEY_ENTER:
                    
                	if (telas != 2 )
                	{
                		telas++;
                	}
                	else
                	{
                		telas = 0;
                	}

                    break;
                }
			break;

			case ALLEGRO_EVENT_TIMER:
				desenhar = 1;
			
			break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				terminar = 1;
			break;

			

			default:
			printf("evento desconhecido\n");
		}


		if (telas == 0)
		{
			al_draw_scaled_bitmap(menu,  0, 0 , 960 , 675 , 1 , 1 , largura, altura , 0);
			al_flip_display();

		}
		if (telas == 1)
		{
			/* code */
		

			if(terminar)
				break;

			if(desenhar && al_is_event_queue_empty(fila_eventos)) 
			{

				desenhar = 0;
				camera_atualiza(cam);
				


				if (contadorJogada <= 50)
				{

					
					switch (rodada)
					{
						//mostrar as cores 
						case 1:
							//desenharTela();

							for (int i = 0; i <= repeat; ++i)
							{
								coresOriginais();
								desenharTela();
								al_flip_display();
								al_rest(1);
								escreverCor(jogadas[i]);
								desenharTela();
								al_flip_display();
								al_rest(1);

							}
							
							repeat++;
							contadorJogada = repeat;
							rodada = 2;

							coresOriginais();
							desenharTela();
							al_flip_display();

						break;

						//vez de reconhecer as cores
						case 2:
				

							verde = 0;
							amarelo = 0;
							vermelho = 0;
							azul = 0;

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


								if(  (h >= 30 && h <= 45)   && (s > 0.5) && (v > 0.55 ) ) 
								{
								 	amarelo++;
								 	matriz[y][x][0] = 255;
									matriz[y][x][1] = 255;
									matriz[y][x][2] = 0;							 
								}

							}

							int tam = 6000;
				
							if (verde > tam || vermelho > tam || azul > tam || amarelo > tam )
							{

								if (verde > tam)
								{
									countVerde++;
								}

								if (azul > tam)
								{
									countAzul++;
								}

								if (vermelho >tam)
								{
									countVermelho++;
								}

								if (amarelo >tam)
								{
									countAmarelo++;
								}

							}
							else
							{
								countAzul = 1;
								countAmarelo = 1;
								countVermelho = 1;
								countVerde = 1;
							}

							if (repeatVerifica < contadorJogada)
							{
								int qnt = 15;
							
								if (countVerde == qnt)
								{
									printf("Encontrou Verde\n");
									jogadas_jogador[repeatVerifica] = VERDE;
									coresOriginais();
									destacarVerde();
									desenharTela();
									al_flip_display();
									escreverCor(VERDE);
									al_rest(1);
									coresOriginais();
									repeatVerifica++;

									countAzul = 1;
									countAmarelo = 1;
									countVermelho = 1;
									countVerde = 1;

								}

								if (countVermelho == qnt)
								{
									printf("Encontrou vermelho\n");
									jogadas_jogador[repeatVerifica] = VERMELHO;
									repeatVerifica++;
									coresOriginais();
									destacarVermelho();
									desenharTela();
									al_flip_display();
									escreverCor(VERMELHO);
									al_rest(1);
									coresOriginais();

									countAzul = 1;
									countAmarelo = 1;
									countVermelho = 1;
									countVerde = 1;

									
								}

								if (countAzul == qnt)
								{
									printf("Encontrou Azul\n");
									jogadas_jogador[repeatVerifica] = AZUL;
									repeatVerifica++;
									coresOriginais();
									destacarAzul();
									desenharTela();
									al_flip_display();
									escreverCor(AZUL);
									al_rest(1);
									coresOriginais();

									countAzul = 1;
									countAmarelo = 1;
									countVermelho = 1;
									countVerde = 1;
								}

								if (countAmarelo == qnt)
								{
									printf("Encontrou amarelo\n");
									jogadas_jogador[repeatVerifica] = AMARELO;
									repeatVerifica++;
									coresOriginais();
									destacarAmarelo();
									desenharTela();
									al_flip_display();
									escreverCor(AMARELO);
									al_rest(1);
									coresOriginais();

									countAzul = 1;
									countAmarelo = 1;
									countVermelho = 1;
									countVerde = 1;
								}

							}
							else
							{
								al_rest(1);
								rodada = 3;
								verLegal = 0;
								repeatVerifica = 0;
								coresOriginais();
							}

						break;


						//verificar se a jogada foi correta
						case 3:
							
								

							if (repeatConfere < contadorJogada)
							{
								if (jogadas[repeatConfere] == jogadas_jogador[repeatConfere])
								{
									printf("acertou\n");
								}
								else
								{
									printf("errou\n");
									verLegal++;
								}

								repeatConfere++;
							}
							else
							{

								if (verLegal > 0)
								{
									perder(&telas);
								}
								else
								{
									rodada = 1;
									repeatConfere = 0;
									al_play_sample(moeda, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
								}
							}

						break;
					}

				}
				else
				{
					coresOriginais();
					printf("cabou\n");
				}
				
				
				desenharTela();
				al_flip_display();

				
			}

		}

		if (telas == 2)
		{
			al_draw_scaled_bitmap(fim,  0, 0 , 960 , 675 , 1 , 1 , largura, altura , 0);
			al_flip_display();


			
		 contadorJogada = 0;

			sortearJogadas();


	//CONTROLE DE JOGO
			desenhar = 0;
			terminar = 0;
			sair = 1;

	//CONTROLE DE VERIFICACAO
			repeat = 0;
			repeatVerifica = 0;
			repeatConfere = 0;

	//CONTROLE DA RODADA
			rodada = 1;

	//VARIAVEIS LEGAIS SEM DESCRICAO UTIL
			countAzul = 1;
			countAmarelo = 1;
			countVermelho = 1;
			countVerde = 1;


			verde = 0;
			vermelho = 0;
			azul = 0;
			amarelo = 0;

			

			verLegal = 0;
		}
	//SAIR DO JOGO 
		
	}
	
	al_destroy_display(janela);
	al_destroy_event_queue(fila_eventos);

	return 0;
}