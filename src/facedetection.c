#include "camera.h"
#include "init.h"
#include <stdio.h>

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

		if(n == 0) {
    		//copiaMatriz(cam->quadro, frame_anterior, cam);
    		//toGrayScale(frame_anterior, cam);
    		//binarizacao(frame_anterior, cam, binThreshold);
    		//sobel(frame_anterior, temp, cam, 60);
			copiaMatriz(cam->quadro, fundo, cam);
    		//to_grey_scale(frame_anterior, cam);
			//gauss_filter(frame_anterior, cam, true);
    		sobel(fundo, cam, 50);
    		binarize(fundo, cam, binThreshold);    		
			n = 1;
		}

		if(desenhar && al_is_event_queue_empty(game.fila_eventos)) {
			desenhar = false;
			camera_atualiza(cam);

	    	//copiaMatriz(cam->quadro, frameAtual, cam);
	    	//toGrayScale(frameAtual, cam);
	    	//binarize(frameAtual, cam, binThreshold);

	    	//binarizacao(frameAtual, cam, binThreshold);
	    	//dist_euclid(frameAtual, frame_anterior, temp, cam, 20);
	    	//frameAtual = temp;

	    	//copiaMatriz(cam->quadro, frameAtual, cam);
	    	//to_grey_scale(frameAtual, cam);
	    	//gauss_filter(frame_anterior, cam, true);
	    	//binarize(frameAtual, cam, binThreshold);
	    	//sobel(frameAtual, cam, 60);
	    	//binarize(frameAtual, cam, binThreshold);
	    	//euclidian_distance(frameAtual, frame_anterior, cam, 20);


      		// Vini
			copiaMatriz(cam->quadro, frameAtual, cam);
	    	//to_grey_scale(frameAtual, cam);
	    	sobel(frameAtual, cam, 50);
			binarize(frameAtual, cam, binThreshold);
			euclidian_overlay(frameAtual, fundo, cam, 120);
	    	//gauss_filter(frameAtual, cam, true);
			
	    	is_face(frameAtual, cam->quadro, 0, 0, cam->largura / 4, cam->altura/2);

			camera_copia(cam, cam->quadro, esquerda);
      		//camera_copia(cam, frameAtual, direita);
			camera_copia(cam, frameAtual, direita);

			al_draw_line(cam->largura, cam->altura/4, cam->largura*2, cam->altura/4, color, 5);
			al_draw_line(cam->largura, cam->altura/2, cam->largura*2, cam->altura/2, color, 5);
			al_draw_line(cam->largura * 1.25, 0, cam->largura * 1.25, cam->altura, color, 5);


			al_flip_display();
			//copiaMatriz(frameAtual, frame_anterior, cam);
		}
	}

	al_destroy_bitmap(direita);
	al_destroy_bitmap(esquerda);
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

  	ALLEGRO_COLOR color = al_map_rgb_f(1, 0, 0);

	largura = end_x - start_x;
	altura = end_y - start_y;

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

	/*
	if (facecounter >= 200) {
		for (i = start_x; i < end_x; i++) {
			for (j = start_y; j < end_y; j++) {

				matrix[j][i][0] = alvo[j][i][0];
				matrix[j][i][1] = alvo[j][i][1];
				matrix[j][i][2] = alvo[j][i][2];
			}
		}
	}
	*/

	al_draw_circle(largura/2, altura/2, (altura)/2, color, 2); 

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