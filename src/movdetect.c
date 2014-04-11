/*#include "camera.h"
#include "init.h"
#include <stdio.h>

void movdetect()
{
	camera *cam = camera_inicializa(0);
	//INICIALIZAR ALLEGRO
	inicializar(cam);
	printf("Inicializou\n");
	al_start_timer(game.timer);
	int i, j, n = 0, pontos = 0;
	bool sair = false;
	bool desenhar = false;
	int threshold = 60;

	int r, g, b;
	int r2, g2, b2;

	unsigned char ***resultado = camera_aloca_matriz(cam);
	unsigned char ***resultado2 = camera_aloca_matriz(cam);
	unsigned char ***frameAnterior = camera_aloca_matriz(cam);

	ALLEGRO_BITMAP *buffer = al_get_backbuffer(game.janela);

  	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, cam->largura, cam->altura);
  	ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, cam->largura, 0, cam->largura, cam->altura);


	//GAME LOOP
	while(!sair)
	{
		//RECEBER EVENTOS
		ALLEGRO_EVENT ev;
        al_wait_for_event(game.fila_eventos, &ev);
   		switch(ev.type)
   		{
			case ALLEGRO_EVENT_TIMER:
   				desenhar = true;
			break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
  				sair = true;
  			break;
   			default:
   				printf("evento desconhecido\n");
    	}

    	if(n == 0)
    	{
    		copiaMatriz(frameAnterior, cam);
    		n = 1;
    	}
             
        if(desenhar && al_is_event_queue_empty(game.fila_eventos))
   		{

      		desenhar = false;
			 
      		camera_atualiza(cam);
	    	
	    	for(i = 0; i < cam->altura; i++)
	    	{
	    		for(j = 0; j < cam->largura; j++)
	    		{
	    			r = cam->quadro[i][j][0];
	    			g = cam->quadro[i][j][1];
	    			b = cam->quadro[i][j][2];

	    			r -= frameAnterior[i][j][0];
	    			g -= frameAnterior[i][j][1];
	    			b -= frameAnterior[i][j][2];

	    			r *= r;
	    			g *= g;
	    			b *= b;

	    			r = r + g + b;
	    			
	    			if (r > (threshold * threshold)) {
	    				resultado[i][j][0] = 255;
	    				resultado[i][j][1] = 255;
	    				resultado[i][j][2] = 255;
	    			} else {	    				
	    				resultado[i][j][0] = 0;
	    				resultado[i][j][1] = 0;
	    				resultado[i][j][2] = 0;
	    			}	    			
	    		}
	    	}

      		camera_copia(cam, frameAnterior, esquerda);
      		camera_copia(cam, resultado, direita);
      		 
      		al_flip_display();
      		copiaMatriz(frameAnterior, cam);
    	}
	}

	al_destroy_bitmap(esquerda);
	al_destroy_bitmap(direita);
	camera_libera_matriz(cam, resultado);
	camera_libera_matriz(cam, resultado2);
	camera_libera_matriz(cam, frameAnterior);
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
}*/