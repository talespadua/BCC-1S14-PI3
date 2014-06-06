#include <stdio.h>

#include "camera.h"
#include "init.h"
#include "sub_matriz.h"
#include "sm_functions.h"

int is_face(unsigned char ***matrix, unsigned char ***alvo, int start_x, int start_y, int end_x, int end_y);
void euclidian_overlay(unsigned char ***frame_atual, unsigned char ***frame_anterior, camera *cam, int threshold);

void face_main() {
	camera *cam = camera_inicializa(0);
	//INICIALIZAR ALLEGRO
	inicializar(cam);
	printf("Inicializou\n");
	al_start_timer(game.timer);
	//int i, j, 
	int n = 0;
	bool sair = false;
	bool desenhar = false;
	///int threshold = 30;
	int binThreshold = 60;

  	ALLEGRO_COLOR color = al_map_rgb_f(1, 0, 0);

	unsigned char ***frameAtual = camera_aloca_matriz(cam);
	unsigned char ***temp = camera_aloca_matriz(cam);
	unsigned char ***frame_anterior = camera_aloca_matriz(cam);
	unsigned char ***fundo = camera_aloca_matriz(cam);

	ALLEGRO_BITMAP *buffer = al_get_backbuffer(game.janela);

	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, cam->largura, cam->altura);
	ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, cam->largura, 0, cam->largura, cam->altura);

	// Sub Matriz
	int startx, starty, endx, endy;
	startx = cam->largura / 2;
	starty = cam->altura / 4;
	
	endx = startx + cam->largura / 4;
	endy = starty + cam->altura / 2;

	sub_matriz *sm = sm_aloca(endy - starty, endx - startx);	
	sub_matriz *sm_aux = sm_aloca(sm->altura, sm->largura);

    //GAME LOOP
	while(!sair) {
		//RECEBER EVENTOS
		ALLEGRO_EVENT ev;
		al_wait_for_event(game.fila_eventos, &ev);
		switch(ev.type) {
			case ALLEGRO_EVENT_TIMER:
			desenhar = true;
			break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			sair = true;
			break;
			default:
			printf("evento desconhecido\n");
		}

		if(n == 70) {
    		//copiaMatriz(cam->quadro, frame_anterior, cam);
    		//toGrayScale(frame_anterior, cam);
    		//binarizacao(frame_anterior, cam, binThreshold);
    		//sobel(frame_anterior, temp, cam, 60);
			copiaMatriz(cam->quadro, fundo, cam);
    		//to_grey_scale(frame_anterior, cam);
			//gauss_filter(frame_anterior, cam, true);
    		//sobel(fundo, cam, 50);
    		//binarize(fundo, cam, binThreshold);    		
			n = 1;
		}

		if(desenhar && al_is_event_queue_empty(game.fila_eventos)) {
			desenhar = false;
			camera_atualiza(cam);


      		// Vini
			copiaMatriz(cam->quadro, frameAtual, cam);
	    	//to_grey_scale(frameAtual, cam);
	    	//sobel(frameAtual, cam, 50);
			//binarize(frameAtual, cam, binThreshold);
			//euclidian_overlay(frameAtual, fundo, cam, 120);
	    	//gauss_filter(frameAtual, cam, true);
			
			// int startx, starty, endx, endy;
			// startx = cam->largura / 2;
			// starty = cam->altura / 4;
			// endx = startx + cam->largura / 4;
			// endy = starty + cam->altura / 2;
	    	
	    	sm_matriz_copy(sm, cam->quadro, startx, starty);
	    	sm_grey_scale(sm);
	    	sm_sobel(sm, sm_aux, 50);
	    	sm_binarize(sm_aux, 50);
	    	sm_matriz_conversion(sm_aux, frameAtual, startx, starty);
	    	sm_matriz_conversion(sm, frameAtual, 0, 0);
	    	sm_matriz_conversion(sm_aux, frameAtual, 0, cam->altura/2);

	    	is_face(frameAtual, cam->quadro, startx, starty, endx, endy);

			camera_copia(cam, cam->quadro, esquerda);
      		//camera_copia(cam, frameAtual, direita);
			camera_copia(cam, frameAtual, direita);

			//al_draw_line(startx, starty, startx, endy, color, 5);
			//al_draw_line(endx, starty, endx, endy, color, 5);
			//al_draw_line(startx, starty, endx, starty, color, 5);
			//al_draw_line(startx, endy, endx, endy, color, 5);

			// al_draw_line(cam->largura, cam->altura/2, cam->largura*2, cam->altura/2, color, 5);
			// al_draw_line(cam->largura * 1.25, 0, cam->largura * 1.25, cam->altura, color, 5);


			al_flip_display();
			//copiaMatriz(frameAtual, frame_anterior, cam);
		}
	}

	al_destroy_bitmap(direita);
	al_destroy_bitmap(esquerda);

	sm_finaliza(sm);
	sm_finaliza(sm_aux);

	camera_libera_matriz(cam, frameAtual);
	camera_libera_matriz(cam, temp);
	camera_libera_matriz(cam, frame_anterior);
	camera_libera_matriz(cam, fundo);
	camera_finaliza(cam);
	
	al_unregister_event_source(game.fila_eventos, al_get_display_event_source(game.janela));
	al_unregister_event_source(game.fila_eventos, al_get_timer_event_source(game.timer));

	al_destroy_event_queue(game.fila_eventos);
	al_destroy_display(game.janela);
	al_destroy_timer(game.timer);

	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_uninstall_system();

	al_stop_timer(game.timer);
}

int is_face(unsigned char ***matrix, unsigned char ***alvo, int start_x, int start_y, int end_x, int end_y) {
	int facecounter = 0;
	int i, j;
	int i_start, j_start, i_end, j_end;
	int largura, altura;
	int total_pixels;
	char pixel_esperado;

	// TODO fazer uma struct deste paranauê aqui
	int left_inix, left_endx, right_inix, right_endx, lip_inix, lip_endx;
	int left_iniy, left_endy, right_iniy, right_endy, lip_iniy, lip_endy;

  	ALLEGRO_COLOR color = al_map_rgb_f(1, 0, 0);

	largura = end_x - start_x;
	altura = end_y - start_y;

	left_inix = start_x + (largura / 7);
	left_endx = start_x + ((largura * 3) / 7);
	left_iniy = start_y + (altura / 5);
	left_endy = start_y + ((altura * 2) / 5);

	right_inix = start_x + ((largura * 2) / 3.5);
	right_endx = start_x + ((largura * 3) / 3.5);
	right_iniy = start_y + (altura / 5); 
	right_endy = start_y + ((altura * 2) / 5);

	lip_inix = start_x + ((largura) / 7);
	lip_endx = start_x + ((largura * 3) / 3.5);
	lip_iniy = start_y + ((altura * 2.75) / 5); 
	lip_endy = start_y + ((altura * 3.5) / 5);

	total_pixels = altura * largura;

	for (i = start_x; i < end_x; i++) {
		for (j = start_y; j < end_y; j++) {

			pixel_esperado = 0;
			// Região onde se espera estar os olhos e a boca
			if (i > left_inix && i < right_endx &&
				j > left_iniy && j < lip_endy) {
				
				pixel_esperado = 255;

				if (j < lip_iniy) {
					if (j > left_endy || i > left_endx && i < right_inix) {
						pixel_esperado = 0;

						if (matrix[j][i][0] == 255) {
							facecounter--;
						}	
					} else {	
						if (matrix[j][i][0] == 255) {
							facecounter++;
						}	

						// olhos
						matrix[j][i][0] = matrix[j][i][0];
						matrix[j][i][1] = matrix[j][i][1];
						matrix[j][i][2] = 255;
					}
				} else {		
					if (matrix[j][i][0] == 255) {
						facecounter++;
					}	

					// boca
					matrix[j][i][0] = matrix[j][i][0];
					matrix[j][i][1] = 255;
					matrix[j][i][2] = matrix[j][i][2];
				}
			}
		}
	}
	
	total_pixels = ((left_endy - left_iniy) * (left_endx - left_inix));
	//total_pixels *= 2;
	total_pixels += ((lip_endy - lip_iniy) * (lip_endx - lip_inix));

	printf("\n\n\nfacecounter: %d, total_pixels: %d\n\n\n", facecounter, total_pixels);
	
	if (facecounter > ((total_pixels * 13) / 100)) {
		for (i = start_x; i < end_x; i++) {
			for (j = start_y; j < end_y; j++) {
				// matrix[j][i][0] = 0;
				// matrix[j][i][1] = 255;
				// matrix[j][i][2] = 0;

				alvo[j][i][0] = 255;
				alvo[j][i][1] = 0;
				alvo[j][i][2] = 0;
			}
		}
	}
	

	/*
  	// olho esquerdo
	i_start = start_x + (largura / 7);
	j_start = start_y + (altura / 5);
	
	i_end = start_x + ((largura * 3) / 7);
	j_end = start_y + ((altura * 2) / 5);

	for (i = i_start; i < i_end; i++) {
		for  (j = j_start; j < j_end; j++) {

			if (matrix[j][i][0] == 255) {
				facecounter++;
			}

			matrix[j][i][0] = 0;
			matrix[j][i][1] = 0;
			matrix[j][i][2] = 255;
		}
	}

	// olho direito
	i_start = start_x + ((largura * 2) / 3.5);
	j_start = start_y + (altura / 5);
	
	i_end = start_x + ((largura * 3) / 3.5);
	j_end = start_y + ((altura * 2) / 5);

	for (i = i_start; i < i_end; i++) {
		for (j = j_start; j < j_end; j++) {

			if (matrix[j][i][0] == 255) {
				facecounter++;
			}

			matrix[j][i][0] = 0;
			matrix[j][i][1] = 0;
			matrix[j][i][2] = 255;
		}
	}

	// boca	
	i_start = start_x + ((largura) / 7);
	j_start = start_y + ((altura * 2.75) / 5);
	
	i_end = start_x + ((largura * 3) / 3.5);
	j_end = start_y + ((altura * 3.5) / 5);

	for (i = i_start; i < i_end; i++) {
		for (j = j_start; j < j_end; j++) {

			if (matrix[j][i][0] == 255) {
				facecounter++;
			}

			matrix[j][i][0] = 0;
			matrix[j][i][1] = 0;
			matrix[j][i][2] = 255;
		}
	} */

	// al_draw_circle(largura/2, altura/2, (altura)/2, color, 2); 

	return 1;
}

void euclidian_overlay(unsigned char ***frame_atual, unsigned char ***frame_anterior, camera *cam, int threshold) {
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
			
			frame_atual[i][j][0] = (r > threshold) ? frame_atual[i][j][0] : 0;
			frame_atual[i][j][1] = (r > threshold) ? frame_atual[i][j][1] : 0;
			frame_atual[i][j][2] = (r > threshold) ? frame_atual[i][j][2] : 0;
			
			// frame_atual[i][j][0] = (r > threshold) ? 0 : 255;
			// frame_atual[i][j][1] = (r > threshold) ? 0 : 255;
			// frame_atual[i][j][2] = (r > threshold) ? 0 : 255;
		}
	}
}