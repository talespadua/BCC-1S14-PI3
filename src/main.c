#include "init.h"
#include "camera.h"
#include "movdetect.h"
#include "flappybino.h"
#include "sobel.h"

void QuitGame()
{
    printf("Teste2\n");
}

int main()
{
	camera *cam = camera_inicializa(0);

	inicializar(cam);
	printf("Inicializou\n");
	al_start_timer(game.timer);

	bool desenhar = false;
	bool sair = false;

	ALLEGRO_BITMAP *buffer = al_get_backbuffer(game.janela);

	ALLEGRO_BITMAP *fundo_original = al_load_bitmap("../img/menu_tosco.png");
	//ALLEGRO_BITMAP *fundo = al_create_bitmap(cam->largura, cam->altura);

	//stretch_blit(fundo_original, fundo, 0, 0, 800, 600, 0, 0, cam->largura, cam->altura);
	//al_destroy_bitmap(fundo_original);

  	ALLEGRO_BITMAP *esquerda = al_create_sub_bitmap(buffer, 0, 0, cam->largura, cam->altura);
  	ALLEGRO_BITMAP *direita = al_create_sub_bitmap(buffer, cam->largura, 0, cam->largura, cam->altura);

  	while(!sair)
  	{
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
    		camera_copia(cam, cam->quadro, esquerda);
		    al_draw_scaled_bitmap(fundo_original, 0, 0, 800, 600, cam->largura, 0, cam->largura, cam->altura, 0);
		    al_flip_display();
    	}
  	}  	

  	al_destroy_bitmap(direita);
	al_destroy_bitmap(esquerda);
	al_destroy_bitmap(fundo_original);
	al_destroy_bitmap(buffer);

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
	//start_flappy_bino();  
	//movdetect();
	//sobel_main();
  	return 0;
}