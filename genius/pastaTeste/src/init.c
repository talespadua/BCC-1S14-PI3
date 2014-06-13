#include "init.h"
#include "camera.h"


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

    timer = al_create_timer(1.0 / 60);
    if(!timer)
        erro("erro na criacao do relogio\n");

    fila_eventos = al_create_event_queue();

    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }

    cam = camera_inicializa(0);
    if(!cam)
        erro("erro na inicializacao da camera\n");

    largura = cam->largura;
    altura = cam->altura;

    timer = al_create_timer(1.0 / 60);
    if(!timer)
        erro("erro na criacao do relogio\n");

    display = al_create_display(2 * largura, altura);
    if(!display)
        erro("erro na criacao da janela\n");

    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_display_event_source(display));

    

    matriz = camera_aloca_matriz(cam);
    cor = al_map_rgb_f(0, 0, 1);
    buffer = al_get_backbuffer(display);
    esquerda = al_create_sub_bitmap(buffer, 0, 0, largura, altura);
    direita = al_create_sub_bitmap(buffer, largura, 0, largura, altura);


    /*
    janela = al_create_display(800, 600);

    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }

    al_set_window_title(janela, "Allegro");

    
    */
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
   // al_register_event_source(fila_eventos, al_get_keyboard_event_source());
   // al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return true;
}