#include "camera.h"
#include "init.h"
#include <stdio.h>

void sobel()
{
	camera *cam = camera_inicializa(0);
	//INICIALIZAR ALLEGRO
	inicializar(cam);
	printf("Inicializou\n");
	al_start_timer(game.timer);
	int i, j, n = 0, pontos = 0, somaJ = 0, somaI = 0;
	bool sair = false;
	bool desenhar = false;
	int threshold = 0;

	unsigned char ***resultado = camera_aloca_matriz(cam);
	unsigned char ***temp = camera_aloca_matriz(cam);

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

    	if(desenhar && al_is_event_queue_empty(game.fila_eventos))
   		{

      		desenhar = false;
			 
      		camera_atualiza(cam);
	    	
	    	toGrayScale(resultado, cam);

	    	for(i = 1; i < cam->altura-1; i++)
	    	{
	    		for(j = 1; j < cam->largura-1; j++)
	    		{
	    			somaJ = ((-1*resultado[i-1][j-1][0]) +
							(resultado[i-1][j+1][0]) +
							(-2*resultado[i][j-1][0]) +
							(2*resultado[i][j+1][0]) +
							(-1*resultado[i+1][j-1][0]) +
							(resultado[i+1][j+1][0]));

					somaI = ((resultado[i-1][j-1][0])+
							(-1*resultado[i+1][j-1][0]) +
							(2*resultado[i-1][j][0]) +
							(-2*resultado[i+1][j][0]) + 
							(resultado[i-1][j+1][0]) + 
							(-1*resultado[i+1][j+1][0]));

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

					temp[i][j][0] = somaJ+somaI;
					temp[i][j][1] = somaJ+somaI;
					temp[i][j][2] = somaJ+somaI;
	    		}
	    	}

	    	//resultado = temp;
      		camera_copia(cam, cam->quadro, esquerda);
      		camera_copia(cam, temp, direita);
      		 
      		al_flip_display();
    	}
	}

	al_destroy_bitmap(direita);
	camera_libera_matriz(cam, resultado);
	camera_libera_matriz(cam, temp);
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