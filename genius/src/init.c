#include "init.h"
#include "camera.h"


void erro(char *mensagem) 
{
    fputs(mensagem, stderr);
    exit(EXIT_FAILURE);
}

bool inicializar()
{
    //INICIALIZAR ADD ONS DO ALLEGRO
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }

    if(!al_install_audio())
    {
        fprintf(stderr, "failed to initialize audio!\n");
        return -1;
    }
 
   if(!al_init_acodec_addon())
   {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        return -1;
   }
 
   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
 
    sample1 = al_load_sample( "../music/song1.wav" );
    sample2 = al_load_sample( "../music/song2.wav" );
    sample3 = al_load_sample( "../music/song3.wav" );
    sample4 = al_load_sample( "../music/song4.wav" );
    moeda = al_load_sample( "../music/coin.WAV" );
    peido = al_load_sample( "../music/wetfart.wav" );

   

    if (!menu)
    {
        printf("deu merda\n");
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
    {
        erro("erro na criacao do relogio\n");
    }
        

    fila_eventos = al_create_event_queue();


    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }

    
    cam = camera_inicializa(0);

    if(!cam)
    {
        erro("erro na inicializacao da camera\n");
    }
        

    largura = cam->largura;
    altura = cam->altura;


    display = al_create_display( largura, altura);

    if(!display)
    {
        erro("erro na criacao da janela\n");
    }
        

    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(display));

    

    matriz = camera_aloca_matriz(cam);
    cor_verde = al_map_rgb_f(0, 0.35, 0);
    cor_vermelha = al_map_rgb_f(0.35, 0, 0);
    cor_azul = al_map_rgb_f(0, 0, 0.35);
    cor_amarelo = al_map_rgb_f(0.35, 0.35, 0);
    buffer = al_get_backbuffer(display);

     menu = al_load_bitmap("menu.jpg");
     fim = al_load_bitmap("../img/fim.jpg");
   // esquerda = al_create_sub_bitmap(buffer, 0, 0, largura, altura);
    //direita = al_create_sub_bitmap(buffer, largura, 0, largura, altura);

    return true;
}