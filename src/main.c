#include "init.h"

int main()
{
	//INICIALIZAR ALLEGRO
	inicializar();

	int sair = 1;

	//GAME LOOP
	while(sair)
	{
		//RECEBER EVENTOS
		while(!al_is_event_queue_empty(fila_eventos))
        {
        	ALLEGRO_EVENT ev;
            al_wait_for_event(fila_eventos, &ev);

      		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = 0;
            } 
        }

		al_draw_bitmap(teste, 0, 0, 0);
		//EXIBIR DISPLAY
		al_flip_display();
	}

	ALLEGRO_CONFIG* cfg = al_load_config_file("config/allegro.cfg");
	printf("%s\n", al_get_config_value(cfg, "weapon 0", "damage")); /* Prints: 443 */

	//SAIR DO JOGO 
	al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

	return 0;
}