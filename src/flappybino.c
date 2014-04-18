#include "camera.h"
#include "init.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

void flappy_copia_matriz(unsigned char ***matriz, camera *cam) {
	int i, j;
	for(i = 0; i < cam->altura; i++) {
		for(j = 0; j < cam->largura; j++) {
			matriz[i][j][0] = cam->quadro[i][j][0];
			matriz[i][j][1] = cam->quadro[i][j][1];
			matriz[i][j][2] = cam->quadro[i][j][2];
		}
	}
}

void draw_circle(int center_x, int center_y);

void start_flappy_bino() {
	ALLEGRO_BITMAP *buffer, *esquerda, *direita;
	unsigned char ***resultado, ***frame_anterior;
	bool sair = false, desenhar = false;
	
	int r, g, b, i, j, gscale, sobel, n = 0;
	int threshold = 100, y = 0, count = 0, flag = 0, y_anterior = 0, y_info = 600;
	
	camera *cam = camera_inicializa(0);

	//INICIALIZAR ALLEGRO
	inicializar(cam);
	printf("Inicializou\n");
	al_start_timer(game.timer);
	
	resultado = camera_aloca_matriz(cam);
	frame_anterior = camera_aloca_matriz(cam);

	buffer = al_get_backbuffer(game.janela);

  	esquerda = al_create_sub_bitmap(buffer, 0, 0, cam->largura, cam->altura);
  	direita = al_create_sub_bitmap(buffer, cam->largura, 0, cam->largura, cam->altura);

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
    		flappy_copia_matriz(frame_anterior, cam);
    		n = 1;
    	}
             
        if(desenhar && al_is_event_queue_empty(game.fila_eventos)) {
      		desenhar = false;			 
      		camera_atualiza(cam);	    	
	    	
	    	///*
	    	for(i = 0; i < cam->altura; i++) {
	    		for(j = 0; j < cam->largura; j++) {
	    			r = cam->quadro[i][j][0];
	    			g = cam->quadro[i][j][1];
	    			b = cam->quadro[i][j][2];

	    			gscale = (r + g + b) / 3;
	    			resultado[i][j][0] = gscale;
	    			resultado[i][j][1] = gscale;
	    			resultado[i][j][2] = gscale;
	    		}
	    	}

	    	for(i = 0; i < cam->altura; i++) {
	    		for(j = 0; j < cam->largura; j++) {
					if (i == 0 || i == cam->altura-1 || j == 0 || j == cam->largura - 1) {
	    				continue;
	    			}

	    			int r1, r2, r3;
	    			int g1, g2, g3;
	    			int b1, b2, b3;

	    			r1 = resultado[i-1][j-1][0];
	    			r2 = resultado[i-1][j+0][0];
	    			r3 = resultado[i-1][j+1][0];

	    			g1 = resultado[i+0][j-1][0];
	    			g2 = resultado[i+0][j+0][0];
	    			g3 = resultado[i+0][j+1][0];

	    			b1 = resultado[i+1][j-1][2];
	    			b2 = resultado[i+1][j+0][2];
	    			b3 = resultado[i+1][j+1][2];
	    		}
	    	}

	    	for(i = 0; i < cam->altura; i++) {
	    		for(j = 0; j < cam->largura; j++) {

	    		}
	    	}


	    	// +r1 2*g1 +b1
	    	// 0 0 0
	    	// -r3 -2*g3 -b3

	    	int minha_altura_max = cam->altura - 10;

      		camera_copia(cam, cam->quadro, esquerda);
      		camera_copia(cam, resultado, direita);

			// Tira a média do movimento
      		y /= count;   
      		
      		// Bastante movimentação para cima
      		if (count > 50000 && y > y_anterior + 100) {      
      			// Faz o objeto subir	
      			y_info -= cam->altura/20;
      			draw_circle(cam->largura + cam->largura/2, y_info);
      		} 
      		// Pouca movimentação
      		else {
      			// O objeto decai
      			y_info += 5;

    			if (y_info < minha_altura_max) {
     				draw_circle(cam->largura + cam->largura/2, y_info);
	    		} else {	    			
	    			draw_circle(cam->largura + cam->largura/2, minha_altura_max);
	    		}
      		}

	    	//al_draw_circle(100, 100, 100, cor, 1);
      		 
      		if (flag == 0) {
      			flag = 1;
      		} else {
      			y = 0;
      			count = 0;
      		}

      		y_anterior = y;
      		al_flip_display();
      		flappy_copia_matriz(frame_anterior, cam);
    	}
	}

	al_destroy_bitmap(esquerda);
	al_destroy_bitmap(direita);
	camera_libera_matriz(cam, resultado);
	camera_libera_matriz(cam, frame_anterior);
	//camera_libera_matriz(cam, esquerda);
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


void draw_circle(int center_x, int center_y) {	
	ALLEGRO_COLOR cor = al_map_rgb_f(0, 0, 1);
	al_draw_circle(center_x, center_y, 10, cor, 1);
}