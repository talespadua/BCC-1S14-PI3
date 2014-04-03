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
	
	int r, g, b, i, j, n = 0;
	int threshold = 50, y = 0, count = 0, flag = 0, y_anterior = 0, y_info = 600;
	
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
	    	for(i = 0; i < cam->altura; i++)
	    	{
	    		for(j = 0; j < cam->largura; j++)
	    		{
	    			r = cam->quadro[i][j][0];
	    			g = cam->quadro[i][j][1];
	    			b = cam->quadro[i][j][2];

	    			r -= frame_anterior[i][j][0];
	    			g -= frame_anterior[i][j][1];
	    			b -= frame_anterior[i][j][2];

	    			r *= r;
	    			g *= g;
	    			b *= b;

	    			r = r + g + b;
	    			
	    			// Para cada pixel, calcula distancia euclidiana
	    			if (r > (threshold * threshold)) {	
	    				resultado[i][j][0] = 255;
	    				resultado[i][j][1] = 255;
	    				resultado[i][j][2] = 255;

	    				// Contador para tirar uma média de movimento dos pixeis
	    				y += i;
	    				count++; 	    			
	    			} else {	    				
	    				resultado[i][j][0] = 0;
	    				resultado[i][j][1] = 0;
	    				resultado[i][j][2] = 0;
	    			}		
	    		}
	    	}
	    	//*/
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