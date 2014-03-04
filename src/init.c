#include "init.h"
#include "camera.h"

void erro(char *mensagem) {
    fputs(mensagem, stderr);

    exit(EXIT_FAILURE);
}


bool inicializar(camera *cam)
{
    //INICIALIZAR ADD ONS DO ALLEGRO
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }

   	al_init_font_addon();

    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_ttf.\n");
        return false;
    }

    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_primitives.\n");
        return false;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    game.janela = al_create_display(2*cam->largura, cam->altura);

    if (!game.janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }

    al_set_window_title(game.janela, "CV Mini-Games");

    game.fila_eventos = al_create_event_queue();

    if (!game.fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(game.janela);
        return false;
    }

    game.timer = al_create_timer(1.0 / FPS);
    if(!game.timer)
    {
        erro("erro na criacao do timer\n");
        al_destroy_event_queue(game.fila_eventos);
        al_destroy_display(game.janela);
        return false;
    }

    /*MOUSE COMENTADO
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(game.janela);
        return -1;
    }

    if (!al_set_system_mouse_cursor(game.janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(game.janela);
        return -1;
    }*/

    /* JOYSTICK COMENTADO
    if(!al_install_joystick())
    {
        fprintf(stderr, "falha ao inicializar joystick!\n");
    }

    al_reconfigure_joysticks();

    joystick = al_get_joystick(al_get_num_joysticks()-1);

    al_register_event_source(fila_eventos  , al_get_joystick_event_source());
    */

    //INICIALIZAR VARIAVEIS
    game.teste = al_load_bitmap("../img/pika.png");

    if (!game.teste)
    {
        fprintf(stderr, "erro no pikachu.\n");
        return false;
    }

    //REGISTRAR EVENTOS
    al_register_event_source(game.fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(game.fila_eventos, al_get_display_event_source(game.janela));
    al_register_event_source(game.fila_eventos, al_get_timer_event_source(game.timer));

    return true;
}