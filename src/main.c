#include "init.h"
#include "camera.h"
#include "movdetect.h"

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
	movdetect();  	
  	return 0;
}