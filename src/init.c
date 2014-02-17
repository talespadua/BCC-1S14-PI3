#include "init.h"

bool inicializar()
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

    janela = al_create_display(800, 600);

    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }

    al_set_window_title(janela, "Allegro");

    fila_eventos = al_create_event_queue();

    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }

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
    teste = al_load_bitmap("../img/pika.png");

    if (!teste)
    {
        fprintf(stderr, "erro no pikachu.\n");
        return false;
    }

    //REGISTRAR EVENTOS
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return true;
}