/*TODO
	Mudar o nome desse arquivo
*/
#include "camera.h"
#include "init.h"
#include <stdio.h>

void sobel_main()
{
	camera *cam = camera_inicializa(0);
	//INICIALIZAR ALLEGRO
	inicializar(cam);
	printf("Inicializou\n");
	al_start_timer(game.timer);
	int i, j, n = 0;
	bool sair = false;
	bool desenhar = false;
	int threshold = 30;

	unsigned char ***frameAtual = camera_aloca_matriz(cam);
	unsigned char ***temp = camera_aloca_matriz(cam);
	unsigned char ***frame_anterior = camera_aloca_matriz(cam);

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
    		copiaMatriz(cam->quadro, frame_anterior, cam);
    		toGrayScale(frame_anterior, cam);
	    	sobel(frame_anterior, cam, 20);
	    	binarizacao(frame_anterior, cam, 50);
    		n = 1;
    	}

    	if(desenhar && al_is_event_queue_empty(game.fila_eventos))
   		{

      		desenhar = false;
			 
      		camera_atualiza(cam);
	    	copiaMatriz(cam->quadro, frameAtual, cam);
	    	toGrayScale(frameAtual, cam);
	    	sobel(frameAtual, cam, 20);
	    	binarizacao(frameAtual, cam, 20);
	    	dist_euclid(frameAtual, frame_anterior, temp, cam, 20);
	    	//frameAtual = temp;
      		camera_copia(cam, cam->quadro, esquerda);
      		camera_copia(cam, frame_anterior, direita);
      		 
      		al_flip_display();
      		copiaMatriz(frameAtual, frame_anterior, cam);
    	}
	}

	al_destroy_bitmap(direita);
	camera_libera_matriz(cam, frameAtual);
	camera_libera_matriz(cam, temp);
	camera_libera_matriz(cam, frame_anterior);
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