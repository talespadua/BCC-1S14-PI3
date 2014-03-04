#include "camera.h"
#include "init.h"
#include <stdio.h>

void movdetect()
{
	camera *cam = camera_inicializa(1);
	//INICIALIZAR ALLEGRO
	inicializar(cam);
	printf("Inicializou\n");
	al_start_timer(game.timer);
	int i, j;
	bool sair = false;
	bool desenhar = false;

	unsigned char ***resultado = camera_aloca_matriz(cam);

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
	    	
	    	for(i = 0; i < cam->altura; i++)
	    	{
	    		for(j = 0; j < cam->largura; j++)
	    		{
	    			if(cam->quadro[i][j][0] > 150)
	    			{
	    				resultado[i][j][0] = 255;
	    			}
	    			else
	    			{
	    				resultado[i][j][0] = 0;
	    			}
	    		}
	    	}
      		camera_copia(cam, cam->quadro, esquerda);
      		camera_copia(cam, resultado, direita);
      		 
      		al_flip_display();
    	}
	}

	al_destroy_bitmap(esquerda);
	al_destroy_bitmap(direita);
	camera_libera_matriz(cam, resultado);
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