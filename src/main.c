#include "init.h"
#include "camera.h"

void QuitGame()
{
    al_unregister_event_source(game.fila_eventos, al_get_display_event_source(game.janela));
  	al_unregister_event_source(game.fila_eventos, al_get_timer_event_source(game.timer));

	al_destroy_event_queue(game.fila_eventos);
	al_destroy_display(game.janela);
	al_destroy_timer(game.timer);

	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
 	al_uninstall_system();
    printf("Teste2\n");
}

int main()
{
	camera *cam = camera_inicializa(0);
	printf("Inicializou\n");
	//INICIALIZAR ALLEGRO
	inicializar(cam);
	al_start_timer(game.timer);
	int sair = false;
	bool desenhar = false;
	unsigned char ***matriz = camera_aloca_matriz(cam);

	ALLEGRO_BITMAP *buffer = al_get_backbuffer(game.janela);

  	ALLEGRO_BITMAP *imagem = al_create_sub_bitmap(buffer, 0, 0, cam->largura, cam->altura);

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
	    	 
      		camera_copia(cam, cam->quadro, imagem);
      		 
      		//al_draw_bitmap(imagem,0,0,0); // nao rola nao sei pq

            al_flip_display();
    	}
	}

	//ALLEGRO_CONFIG* cfg = al_load_config_file("config/allegro.cfg");
	//printf("%s\n", al_get_config_value(cfg, "weapon 0", "damage")); /* Prints: 443 */

	//SAIR DO JOGO 
	al_destroy_bitmap(imagem);
	camera_finaliza(cam);
	camera_libera_matriz(cam, matriz);

 	al_stop_timer(game.timer);
 	QuitGame();
  	
  	return 0;
}